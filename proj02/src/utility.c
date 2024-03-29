#include "utility.h"
#include "process.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

void seed_rand() {
    static int first_run = 1;
    if (first_run) {
        first_run = 0;
        srand(time(NULL));
    }
}

int get_random_in_range(int range_start, int range_end) {
    seed_rand();
    if (range_start == range_end) return range_start;
    return range_start + rand() / (RAND_MAX / (range_end - range_start + 1) + 1);
}

double get_random_double() {
    seed_rand();
    return (double)rand() / (double)RAND_MAX;
}

int get_exponential_random(int range_average, int range_start, int range_end) {
    seed_rand();

    double lambda = 1.0 / (double)range_average;

    double x;
    do {
        double u = get_random_double();
        x = -log(1 - u) / lambda;
    } while (x < range_start || x > range_end);
    return round(x);
}

long long _simulation_start_time;

long long get_milliseconds() {
    struct timeval time;
    gettimeofday(&time, 0);
    return (time.tv_sec * 1000000 + time.tv_usec) / 1000;
}

void start_simulation_time() {
    _simulation_start_time = start_time();
}

int get_time_since_t0() {
    return end_time(_simulation_start_time);
}

long long start_time() {
    return get_milliseconds();
}

int end_time(long long time_start) {
    return get_milliseconds() - time_start;
}

struct process_statistics* stats_array;

void init_process_stats_array(int max_pid) {
    stats_array = malloc(max_pid * sizeof *stats_array);
}

void send_process_stats(struct process_statistics stats) {
    stats_array[stats.pid - 1] = stats;
}

struct process_statistics* get_process_stats() {
    return stats_array;
}

