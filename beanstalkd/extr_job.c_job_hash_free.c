#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {struct TYPE_6__* ht_next; TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 size_t _get_job_hash_index (int /*<<< orphan*/ ) ; 
 TYPE_2__** all_jobs ; 
 int all_jobs_cap ; 
 int all_jobs_used ; 
 int /*<<< orphan*/  rehash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
job_hash_free(Job *j)
{
    Job **slot;

    slot = &all_jobs[_get_job_hash_index(j->r.id)];
    while (*slot && *slot != j) slot = &(*slot)->ht_next;
    if (*slot) {
        *slot = (*slot)->ht_next;
        --all_jobs_used;
    }

    // Downscale when the hashmap is too sparse
    if (all_jobs_used < (all_jobs_cap >> 4)) rehash(0);
}