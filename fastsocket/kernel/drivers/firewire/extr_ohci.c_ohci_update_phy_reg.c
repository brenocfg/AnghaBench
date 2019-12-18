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
typedef  int u32 ;
struct fw_ohci {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OHCI1394_PhyControl ; 
 int /*<<< orphan*/  OHCI1394_PhyControl_Read (int) ; 
 int OHCI1394_PhyControl_ReadData (int) ; 
 int OHCI1394_PhyControl_ReadDone ; 
 int /*<<< orphan*/  OHCI1394_PhyControl_Write (int,int) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 int /*<<< orphan*/  fw_error (char*) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ohci_update_phy_reg(struct fw_card *card, int addr,
			       int clear_bits, int set_bits)
{
	struct fw_ohci *ohci = fw_ohci(card);
	u32 val, old;

	reg_write(ohci, OHCI1394_PhyControl, OHCI1394_PhyControl_Read(addr));
	flush_writes(ohci);
	msleep(2);
	val = reg_read(ohci, OHCI1394_PhyControl);
	if ((val & OHCI1394_PhyControl_ReadDone) == 0) {
		fw_error("failed to set phy reg bits.\n");
		return -EBUSY;
	}

	old = OHCI1394_PhyControl_ReadData(val);
	old = (old & ~clear_bits) | set_bits;
	reg_write(ohci, OHCI1394_PhyControl,
		  OHCI1394_PhyControl_Write(addr, old));

	return 0;
}