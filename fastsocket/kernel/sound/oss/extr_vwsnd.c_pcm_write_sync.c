#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hwstate; int /*<<< orphan*/  swstate; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vwsnd_port_t ;
typedef  scalar_t__ vwsnd_port_hwstate_t ;
struct TYPE_8__ {TYPE_1__ wport; } ;
typedef  TYPE_2__ vwsnd_dev_t ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGEV (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  DBGPV (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DBGRV () ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ HW_STOPPED ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void pcm_write_sync(vwsnd_dev_t *devc)
{
	vwsnd_port_t *wport = &devc->wport;
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;
	vwsnd_port_hwstate_t hwstate;

	DBGEV("(devc=0x%p)\n", devc);
	add_wait_queue(&wport->queue, &wait);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_lock_irqsave(&wport->lock, flags);
		{
			hwstate = wport->hwstate;
		}
		spin_unlock_irqrestore(&wport->lock, flags);
		if (hwstate == HW_STOPPED)
			break;
		schedule();
	}
	current->state = TASK_RUNNING;
	remove_wait_queue(&wport->queue, &wait);
	DBGPV("swstate = %d, hwstate = %d\n", wport->swstate, wport->hwstate);
	DBGRV();
}