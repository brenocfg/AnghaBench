#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int sched_mode_t ;
struct TYPE_4__ {scalar_t__ runq; int sched_mode; } ;

/* Variables and functions */
 scalar_t__ PROCESSOR_NULL ; 
#define  TH_MODE_FIXED 130 
#define  TH_MODE_REALTIME 129 
#define  TH_MODE_TIMESHARE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  sched_update_thread_bucket (TYPE_1__*) ; 

void
sched_set_thread_mode(thread_t thread, sched_mode_t new_mode)
{
	assert(thread->runq == PROCESSOR_NULL);

	switch (new_mode) {
	case TH_MODE_FIXED:
	case TH_MODE_REALTIME:
	case TH_MODE_TIMESHARE:
		break;

	default:
		panic("unexpected mode: %d", new_mode);
		break;
	}

	thread->sched_mode = new_mode;

	sched_update_thread_bucket(thread);
}