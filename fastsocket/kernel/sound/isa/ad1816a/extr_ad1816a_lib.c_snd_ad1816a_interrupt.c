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
struct snd_ad1816a {int /*<<< orphan*/  lock; TYPE_1__* timer; scalar_t__ capture_substream; scalar_t__ playback_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  sticks; } ;

/* Variables and functions */
 unsigned char AD1816A_CAPTURE_IRQ_PENDING ; 
 int /*<<< orphan*/  AD1816A_INTERRUPT_STATUS ; 
 unsigned char AD1816A_PLAYBACK_IRQ_PENDING ; 
 unsigned char AD1816A_TIMER_IRQ_PENDING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char snd_ad1816a_in (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ad1816a_out (struct snd_ad1816a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  snd_timer_interrupt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_ad1816a_interrupt(int irq, void *dev_id)
{
	struct snd_ad1816a *chip = dev_id;
	unsigned char status;

	spin_lock(&chip->lock);
	status = snd_ad1816a_in(chip, AD1816A_INTERRUPT_STATUS);
	spin_unlock(&chip->lock);

	if ((status & AD1816A_PLAYBACK_IRQ_PENDING) && chip->playback_substream)
		snd_pcm_period_elapsed(chip->playback_substream);

	if ((status & AD1816A_CAPTURE_IRQ_PENDING) && chip->capture_substream)
		snd_pcm_period_elapsed(chip->capture_substream);

	if ((status & AD1816A_TIMER_IRQ_PENDING) && chip->timer)
		snd_timer_interrupt(chip->timer, chip->timer->sticks);

	spin_lock(&chip->lock);
	snd_ad1816a_out(chip, AD1816A_INTERRUPT_STATUS, 0x00);
	spin_unlock(&chip->lock);
	return IRQ_HANDLED;
}