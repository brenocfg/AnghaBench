#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* ht_next; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int NUM_PRIMES ; 
 TYPE_1__** all_jobs ; 
 size_t all_jobs_cap ; 
 TYPE_1__** all_jobs_init ; 
 size_t all_jobs_used ; 
 TYPE_1__** calloc (size_t,int) ; 
 int cur_prime ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int hash_table_was_oom ; 
 size_t* primes ; 
 int /*<<< orphan*/  store_job (TYPE_1__*) ; 
 int /*<<< orphan*/  twarnx (char*,size_t) ; 

__attribute__((used)) static void
rehash(int is_upscaling)
{
    Job **old = all_jobs;
    size_t old_cap = all_jobs_cap, old_used = all_jobs_used, i;
    int old_prime = cur_prime;
    int d = is_upscaling ? 1 : -1;

    if (cur_prime + d >= NUM_PRIMES) return;
    if (cur_prime + d < 0) return;
    if (is_upscaling && hash_table_was_oom) return;

    cur_prime += d;

    all_jobs_cap = primes[cur_prime];
    all_jobs = calloc(all_jobs_cap, sizeof(Job *));
    if (!all_jobs) {
        twarnx("Failed to allocate %zu new hash buckets", all_jobs_cap);
        hash_table_was_oom = 1;
        cur_prime = old_prime;
        all_jobs = old;
        all_jobs_cap = old_cap;
        all_jobs_used = old_used;
        return;
    }
    all_jobs_used = 0;
    hash_table_was_oom = 0;

    for (i = 0; i < old_cap; i++) {
        while (old[i]) {
            Job *j = old[i];
            old[i] = j->ht_next;
            j->ht_next = NULL;
            store_job(j);
        }
    }
    if (old != all_jobs_init) {
        free(old);
    }
}