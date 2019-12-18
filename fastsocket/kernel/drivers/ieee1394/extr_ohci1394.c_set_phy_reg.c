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
typedef  int u8 ;
typedef  int u32 ;
struct ti_ohci {int /*<<< orphan*/  phy_reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OHCI1394_PhyControl ; 
 int OHCI_LOOP_COUNT ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_phy_reg(struct ti_ohci *ohci, u8 addr, u8 data)
{
	int i;
	unsigned long flags;
	u32 r = 0;

	spin_lock_irqsave (&ohci->phy_reg_lock, flags);

	reg_write(ohci, OHCI1394_PhyControl, (addr << 8) | data | 0x00004000);

	for (i = 0; i < OHCI_LOOP_COUNT; i++) {
		r = reg_read(ohci, OHCI1394_PhyControl);
		if (!(r & 0x00004000))
			break;

		mdelay(1);
	}

	if (i == OHCI_LOOP_COUNT)
		PRINT (KERN_ERR, "Set PHY Reg timeout [0x%08x/0x%08x/%d]",
		       r, r & 0x00004000, i);

	spin_unlock_irqrestore (&ohci->phy_reg_lock, flags);

	return;
}