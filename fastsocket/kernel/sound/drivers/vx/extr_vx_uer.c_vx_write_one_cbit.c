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
struct vx_core {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUER ; 
 int /*<<< orphan*/  RUER ; 
 int XX_UER_CBITS_OFFSET_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ vx_is_pcmcia (struct vx_core*) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vx_outl (struct vx_core*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx_write_one_cbit(struct vx_core *chip, int index, int val)
{
	unsigned long flags;
	val = !!val;	/* 0 or 1 */
	spin_lock_irqsave(&chip->lock, flags);
	if (vx_is_pcmcia(chip)) {
		vx_outb(chip, CSUER, 0); /* write */
		vx_outb(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	} else {
		vx_outl(chip, CSUER, 0); /* write */
		vx_outl(chip, RUER, (val << 7) | (index & XX_UER_CBITS_OFFSET_MASK));
	}
	spin_unlock_irqrestore(&chip->lock, flags);
}