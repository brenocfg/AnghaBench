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
struct TYPE_4__ {scalar_t__ fraction; scalar_t__ cur_tick; } ;
struct TYPE_3__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct snd_seq_timer {int /*<<< orphan*/  lock; TYPE_2__ tick; TYPE_1__ cur_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_seq_timer_reset(struct snd_seq_timer * tmr)
{
	unsigned long flags;

	spin_lock_irqsave(&tmr->lock, flags);

	/* reset time & songposition */
	tmr->cur_time.tv_sec = 0;
	tmr->cur_time.tv_nsec = 0;

	tmr->tick.cur_tick = 0;
	tmr->tick.fraction = 0;

	spin_unlock_irqrestore(&tmr->lock, flags);
}