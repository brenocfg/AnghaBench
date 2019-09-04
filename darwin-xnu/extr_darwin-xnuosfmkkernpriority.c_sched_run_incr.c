#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {int state; int /*<<< orphan*/  th_sched_bucket; } ;

/* Variables and functions */
 size_t TH_BUCKET_RUN ; 
 int TH_IDLE ; 
 int TH_RUN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sched_incr_bucket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sched_run_buckets ; 

uint32_t
sched_run_incr(thread_t thread)
{
	assert((thread->state & (TH_RUN|TH_IDLE)) == TH_RUN);

	uint32_t new_count = hw_atomic_add(&sched_run_buckets[TH_BUCKET_RUN], 1);

	sched_incr_bucket(thread->th_sched_bucket);

	return new_count;
}