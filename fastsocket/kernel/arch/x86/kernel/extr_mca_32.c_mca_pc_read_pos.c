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
struct mca_device {int pos_register; int slot; unsigned char* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCA_ADAPTER_SETUP_REG ; 
 int /*<<< orphan*/  MCA_MOTHERBOARD_SETUP_REG ; 
 int /*<<< orphan*/  MCA_POS_REG (int) ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mca_lock ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char mca_pc_read_pos(struct mca_device *mca_dev, int reg)
{
	unsigned char byte;
	unsigned long flags;

	if (reg < 0 || reg >= 8)
		return 0;

	spin_lock_irqsave(&mca_lock, flags);
	if (mca_dev->pos_register) {
		/* Disable adapter setup, enable motherboard setup */

		outb_p(0, MCA_ADAPTER_SETUP_REG);
		outb_p(mca_dev->pos_register, MCA_MOTHERBOARD_SETUP_REG);

		byte = inb_p(MCA_POS_REG(reg));
		outb_p(0xff, MCA_MOTHERBOARD_SETUP_REG);
	} else {

		/* Make sure motherboard setup is off */

		outb_p(0xff, MCA_MOTHERBOARD_SETUP_REG);

		/* Read the appropriate register */

		outb_p(0x8|(mca_dev->slot & 0xf), MCA_ADAPTER_SETUP_REG);
		byte = inb_p(MCA_POS_REG(reg));
		outb_p(0, MCA_ADAPTER_SETUP_REG);
	}
	spin_unlock_irqrestore(&mca_lock, flags);

	mca_dev->pos[reg] = byte;

	return byte;
}