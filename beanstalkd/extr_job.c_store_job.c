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
 int _get_job_hash_index (int /*<<< orphan*/ ) ; 
 TYPE_2__** all_jobs ; 
 int all_jobs_cap ; 
 int all_jobs_used ; 
 int /*<<< orphan*/  rehash (int) ; 

__attribute__((used)) static void
store_job(Job *j)
{
    int index = 0;

    index = _get_job_hash_index(j->r.id);

    j->ht_next = all_jobs[index];
    all_jobs[index] = j;
    all_jobs_used++;

    /* accept a load factor of 4 */
    if (all_jobs_used > (all_jobs_cap << 2)) rehash(1);
}