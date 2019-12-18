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
struct sa1111_dev {int dummy; } ;
struct sa1111 {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 int SA1111_AUDIO_I2S ; 
 scalar_t__ SA1111_SKCR ; 
 unsigned int SKCR_SELAC ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 
 unsigned int sa1111_readl (scalar_t__) ; 
 int /*<<< orphan*/  sa1111_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void sa1111_select_audio_mode(struct sa1111_dev *sadev, int mode)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);
	unsigned long flags;
	unsigned int val;

	spin_lock_irqsave(&sachip->lock, flags);

	val = sa1111_readl(sachip->base + SA1111_SKCR);
	if (mode == SA1111_AUDIO_I2S) {
		val &= ~SKCR_SELAC;
	} else {
		val |= SKCR_SELAC;
	}
	sa1111_writel(val, sachip->base + SA1111_SKCR);

	spin_unlock_irqrestore(&sachip->lock, flags);
}