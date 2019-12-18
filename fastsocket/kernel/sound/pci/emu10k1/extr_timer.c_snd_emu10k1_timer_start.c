#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_timer {int sticks; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTE_INTERVALTIMERENB ; 
 scalar_t__ TIMER ; 
 unsigned int TIMER_RATE_MASK ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu10k1_intr_enable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 struct snd_emu10k1* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1_timer_start(struct snd_timer *timer)
{
	struct snd_emu10k1 *emu;
	unsigned long flags;
	unsigned int delay;

	emu = snd_timer_chip(timer);
	delay = timer->sticks - 1;
	if (delay < 5 ) /* minimum time is 5 ticks */
		delay = 5;
	spin_lock_irqsave(&emu->reg_lock, flags);
	snd_emu10k1_intr_enable(emu, INTE_INTERVALTIMERENB);
	outw(delay & TIMER_RATE_MASK, emu->port + TIMER);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return 0;
}