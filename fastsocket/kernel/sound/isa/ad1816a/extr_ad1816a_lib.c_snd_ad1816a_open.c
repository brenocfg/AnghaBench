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
struct snd_ad1816a {unsigned int mode; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_CAPTURE_IRQ_ENABLE ; 
 int /*<<< orphan*/  AD1816A_CAPTURE_IRQ_PENDING ; 
 int /*<<< orphan*/  AD1816A_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  AD1816A_INTERRUPT_STATUS ; 
#define  AD1816A_MODE_CAPTURE 130 
 unsigned int AD1816A_MODE_OPEN ; 
#define  AD1816A_MODE_PLAYBACK 129 
#define  AD1816A_MODE_TIMER 128 
 int /*<<< orphan*/  AD1816A_PLAYBACK_IRQ_ENABLE ; 
 int /*<<< orphan*/  AD1816A_PLAYBACK_IRQ_PENDING ; 
 int /*<<< orphan*/  AD1816A_TIMER_IRQ_ENABLE ; 
 int /*<<< orphan*/  AD1816A_TIMER_IRQ_PENDING ; 
 int EAGAIN ; 
 int /*<<< orphan*/  snd_ad1816a_out_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ad1816a_write_mask (struct snd_ad1816a*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ad1816a_open(struct snd_ad1816a *chip, unsigned int mode)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);

	if (chip->mode & mode) {
		spin_unlock_irqrestore(&chip->lock, flags);
		return -EAGAIN;
	}

	switch ((mode &= AD1816A_MODE_OPEN)) {
	case AD1816A_MODE_PLAYBACK:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_PLAYBACK_IRQ_PENDING, 0x00);
		snd_ad1816a_write_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_PLAYBACK_IRQ_ENABLE, 0xffff);
		break;
	case AD1816A_MODE_CAPTURE:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_CAPTURE_IRQ_PENDING, 0x00);
		snd_ad1816a_write_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_CAPTURE_IRQ_ENABLE, 0xffff);
		break;
	case AD1816A_MODE_TIMER:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_TIMER_IRQ_PENDING, 0x00);
		snd_ad1816a_write_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_TIMER_IRQ_ENABLE, 0xffff);
	}
	chip->mode |= mode;

	spin_unlock_irqrestore(&chip->lock, flags);
	return 0;
}