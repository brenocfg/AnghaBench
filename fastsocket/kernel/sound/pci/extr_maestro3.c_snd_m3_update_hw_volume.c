#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_m3 {int /*<<< orphan*/  ac97_lock; TYPE_3__* master_volume; int /*<<< orphan*/  card; scalar_t__ iobase; TYPE_2__* ac97; TYPE_1__* master_switch; scalar_t__ in_suspend; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 size_t AC97_MASTER_VOL ; 
 scalar_t__ CODEC_COMMAND ; 
 scalar_t__ CODEC_DATA ; 
 scalar_t__ HW_VOL_COUNTER_MASTER ; 
 scalar_t__ HW_VOL_COUNTER_VOICE ; 
 scalar_t__ SHADOW_MIX_REG_MASTER ; 
 scalar_t__ SHADOW_MIX_REG_VOICE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (size_t,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_m3_update_hw_volume(unsigned long private_data)
{
	struct snd_m3 *chip = (struct snd_m3 *) private_data;
	int x, val;
	unsigned long flags;

	/* Figure out which volume control button was pushed,
	   based on differences from the default register
	   values. */
	x = inb(chip->iobase + SHADOW_MIX_REG_VOICE) & 0xee;

	/* Reset the volume control registers. */
	outb(0x88, chip->iobase + SHADOW_MIX_REG_VOICE);
	outb(0x88, chip->iobase + HW_VOL_COUNTER_VOICE);
	outb(0x88, chip->iobase + SHADOW_MIX_REG_MASTER);
	outb(0x88, chip->iobase + HW_VOL_COUNTER_MASTER);

	/* Ignore spurious HV interrupts during suspend / resume, this avoids
	   mistaking them for a mute button press. */
	if (chip->in_suspend)
		return;

	if (!chip->master_switch || !chip->master_volume)
		return;

	/* FIXME: we can't call snd_ac97_* functions since here is in tasklet. */
	spin_lock_irqsave(&chip->ac97_lock, flags);

	val = chip->ac97->regs[AC97_MASTER_VOL];
	switch (x) {
	case 0x88:
		/* mute */
		val ^= 0x8000;
		chip->ac97->regs[AC97_MASTER_VOL] = val;
		outw(val, chip->iobase + CODEC_DATA);
		outb(AC97_MASTER_VOL, chip->iobase + CODEC_COMMAND);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_switch->id);
		break;
	case 0xaa:
		/* volume up */
		if ((val & 0x7f) > 0)
			val--;
		if ((val & 0x7f00) > 0)
			val -= 0x0100;
		chip->ac97->regs[AC97_MASTER_VOL] = val;
		outw(val, chip->iobase + CODEC_DATA);
		outb(AC97_MASTER_VOL, chip->iobase + CODEC_COMMAND);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_volume->id);
		break;
	case 0x66:
		/* volume down */
		if ((val & 0x7f) < 0x1f)
			val++;
		if ((val & 0x7f00) < 0x1f00)
			val += 0x0100;
		chip->ac97->regs[AC97_MASTER_VOL] = val;
		outw(val, chip->iobase + CODEC_DATA);
		outb(AC97_MASTER_VOL, chip->iobase + CODEC_COMMAND);
		snd_ctl_notify(chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->master_volume->id);
		break;
	}
	spin_unlock_irqrestore(&chip->ac97_lock, flags);
}