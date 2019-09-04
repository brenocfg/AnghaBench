#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  mpqueue_head_t ;
struct TYPE_6__ {scalar_t__ deadline; int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {TYPE_1__ rtclock_timer; scalar_t__ cpu_running; } ;
typedef  TYPE_3__ cpu_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  queue; } ;
struct TYPE_9__ {TYPE_2__ rtclock_timer; } ;

/* Variables and functions */
 TYPE_5__* cpu_datap (int /*<<< orphan*/ ) ; 
 TYPE_3__* current_cpu_datap () ; 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  timer_set_deadline (scalar_t__) ; 

mpqueue_head_t *
timer_queue_assign(
    uint64_t        deadline)
{
	cpu_data_t		*cdp = current_cpu_datap();
	mpqueue_head_t		*queue;

	if (cdp->cpu_running) {
		queue = &cdp->rtclock_timer.queue;

		if (deadline < cdp->rtclock_timer.deadline)
			timer_set_deadline(deadline);
	}
	else
		queue = &cpu_datap(master_cpu)->rtclock_timer.queue;

    return (queue);
}