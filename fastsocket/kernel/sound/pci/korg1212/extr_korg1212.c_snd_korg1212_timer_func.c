#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct snd_korg1212 {scalar_t__ stop_pending_cnt; int dsp_stop_is_processed; size_t cardState; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; TYPE_1__* sharedBufferPtr; TYPE_2__ timer; } ;
struct TYPE_3__ {scalar_t__ cardCommand; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  K1212_DEBUG_PRINTK_VERBOSE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * stateName ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_korg1212_timer_func(unsigned long data)
{
        struct snd_korg1212 *korg1212 = (struct snd_korg1212 *) data;
	unsigned long flags;
	
	spin_lock_irqsave(&korg1212->lock, flags);
	if (korg1212->sharedBufferPtr->cardCommand == 0) {
		/* ack'ed */
		korg1212->stop_pending_cnt = 0;
		korg1212->dsp_stop_is_processed = 1;
		wake_up(&korg1212->wait);
		K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: Stop ack'ed [%s]\n",
					   stateName[korg1212->cardState]);
	} else {
		if (--korg1212->stop_pending_cnt > 0) {
			/* reprogram timer */
			korg1212->timer.expires = jiffies + 1;
			add_timer(&korg1212->timer);
		} else {
			snd_printd("korg1212_timer_func timeout\n");
			korg1212->sharedBufferPtr->cardCommand = 0;
			korg1212->dsp_stop_is_processed = 1;
			wake_up(&korg1212->wait);
			K1212_DEBUG_PRINTK("K1212_DEBUG: Stop timeout [%s]\n",
					   stateName[korg1212->cardState]);
		}
	}
	spin_unlock_irqrestore(&korg1212->lock, flags);
}