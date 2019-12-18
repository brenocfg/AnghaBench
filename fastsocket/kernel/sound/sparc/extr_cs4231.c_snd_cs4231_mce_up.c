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
struct snd_cs4231 {int mce_bit; int /*<<< orphan*/  lock; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int CS4231_INIT ; 
 int CS4231_MCE ; 
 int /*<<< orphan*/  REGSEL ; 
 int __cs4231_readb (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cs4231_writeb (struct snd_cs4231*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cs4231_ready (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_printdd (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4231_mce_up(struct snd_cs4231 *chip)
{
	unsigned long flags;
	int timeout;

	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_ready(chip);
#ifdef CONFIG_SND_DEBUG
	if (__cs4231_readb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_printdd("mce_up - auto calibration time out (0)\n");
#endif
	chip->mce_bit |= CS4231_MCE;
	timeout = __cs4231_readb(chip, CS4231U(chip, REGSEL));
	if (timeout == 0x80)
		snd_printdd("mce_up [%p]: serious init problem - "
			    "codec still busy\n",
			    chip->port);
	if (!(timeout & CS4231_MCE))
		__cs4231_writeb(chip, chip->mce_bit | (timeout & 0x1f),
				CS4231U(chip, REGSEL));
	spin_unlock_irqrestore(&chip->lock, flags);
}