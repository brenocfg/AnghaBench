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
struct snd_timer {int dummy; } ;
struct snd_emu10k1 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTE_INTERVALTIMERENB ; 
 int /*<<< orphan*/  snd_emu10k1_intr_disable (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 
 struct snd_emu10k1* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_emu10k1_timer_stop(struct snd_timer *timer)
{
	struct snd_emu10k1 *emu;
	unsigned long flags;

	emu = snd_timer_chip(timer);
	spin_lock_irqsave(&emu->reg_lock, flags);
	snd_emu10k1_intr_disable(emu, INTE_INTERVALTIMERENB);
	spin_unlock_irqrestore(&emu->reg_lock, flags);
	return 0;
}