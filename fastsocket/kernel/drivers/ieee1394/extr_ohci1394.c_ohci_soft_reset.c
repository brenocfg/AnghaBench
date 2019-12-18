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
struct ti_ohci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*) ; 
 int /*<<< orphan*/  OHCI1394_HCControlSet ; 
 int OHCI1394_HCControl_softReset ; 
 int OHCI_LOOP_COUNT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ohci_soft_reset(struct ti_ohci *ohci) {
	int i;

	reg_write(ohci, OHCI1394_HCControlSet, OHCI1394_HCControl_softReset);

	for (i = 0; i < OHCI_LOOP_COUNT; i++) {
		if (!(reg_read(ohci, OHCI1394_HCControlSet) & OHCI1394_HCControl_softReset))
			break;
		mdelay(1);
	}
	DBGMSG ("Soft reset finished");
}