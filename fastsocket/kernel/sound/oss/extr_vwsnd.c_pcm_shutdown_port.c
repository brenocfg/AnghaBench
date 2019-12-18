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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hwstate; scalar_t__ byte_count; int /*<<< orphan*/ * swbuf; int /*<<< orphan*/  chan; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  swstate; } ;
typedef  TYPE_1__ vwsnd_port_t ;
typedef  scalar_t__ vwsnd_port_hwstate_t ;
struct TYPE_8__ {int /*<<< orphan*/  lith; TYPE_1__ rport; } ;
typedef  TYPE_2__ vwsnd_dev_t ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ HW_STOPPED ; 
 int /*<<< orphan*/  SW_INITIAL ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  ad1843_shutdown_adc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ad1843_shutdown_dac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  li_disable_interrupts (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  li_shutdown_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void pcm_shutdown_port(vwsnd_dev_t *devc,
			      vwsnd_port_t *aport,
			      unsigned int mask)
{
	unsigned long flags;
	vwsnd_port_hwstate_t hwstate;
	DECLARE_WAITQUEUE(wait, current);

	aport->swstate = SW_INITIAL;
	add_wait_queue(&aport->queue, &wait);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_lock_irqsave(&aport->lock, flags);
		{
			hwstate = aport->hwstate;
		}		
		spin_unlock_irqrestore(&aport->lock, flags);
		if (hwstate == HW_STOPPED)
			break;
		schedule();
	}
	current->state = TASK_RUNNING;
	remove_wait_queue(&aport->queue, &wait);
	li_disable_interrupts(&devc->lith, mask);
	if (aport == &devc->rport)
		ad1843_shutdown_adc(&devc->lith);
	else /* aport == &devc->wport) */
		ad1843_shutdown_dac(&devc->lith);
	li_shutdown_dma(&aport->chan);
	vfree(aport->swbuf);
	aport->swbuf = NULL;
	aport->byte_count = 0;
}