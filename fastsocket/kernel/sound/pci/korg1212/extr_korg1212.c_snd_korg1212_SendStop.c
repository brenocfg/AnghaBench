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
struct snd_korg1212 {TYPE_2__ timer; scalar_t__ stop_pending_cnt; TYPE_1__* sharedBufferPtr; } ;
struct TYPE_3__ {int cardCommand; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void snd_korg1212_SendStop(struct snd_korg1212 *korg1212)
{
	if (! korg1212->stop_pending_cnt) {
		korg1212->sharedBufferPtr->cardCommand = 0xffffffff;
		/* program the timer */
		korg1212->stop_pending_cnt = HZ;
		korg1212->timer.expires = jiffies + 1;
		add_timer(&korg1212->timer);
	}
}