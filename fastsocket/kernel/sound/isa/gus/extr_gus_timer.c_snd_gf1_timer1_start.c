#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_timer {unsigned int sticks; } ;
struct TYPE_2__ {int timer_enabled; } ;
struct snd_gus_card {int /*<<< orphan*/  reg_lock; TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_GF1_GB_ADLIB_TIMER_1 ; 
 int /*<<< orphan*/  SNDRV_GF1_GB_SOUND_BLASTER_CONTROL ; 
 int /*<<< orphan*/  snd_gf1_adlib_write (struct snd_gus_card*,int,unsigned char) ; 
 int /*<<< orphan*/  snd_gf1_write8 (struct snd_gus_card*,int /*<<< orphan*/ ,unsigned char) ; 
 struct snd_gus_card* snd_timer_chip (struct snd_timer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_gf1_timer1_start(struct snd_timer * timer)
{
	unsigned long flags;
	unsigned char tmp;
	unsigned int ticks;
	struct snd_gus_card *gus;

	gus = snd_timer_chip(timer);
	spin_lock_irqsave(&gus->reg_lock, flags);
	ticks = timer->sticks;
	tmp = (gus->gf1.timer_enabled |= 4);
	snd_gf1_write8(gus, SNDRV_GF1_GB_ADLIB_TIMER_1, 256 - ticks);	/* timer 1 count */
	snd_gf1_write8(gus, SNDRV_GF1_GB_SOUND_BLASTER_CONTROL, tmp);	/* enable timer 1 IRQ */
	snd_gf1_adlib_write(gus, 0x04, tmp >> 2);	/* timer 2 start */
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	return 0;
}