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
struct hpsb_host {struct ti_ohci* hostdata; } ;
typedef  int quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_CSRCompareData ; 
 int /*<<< orphan*/  OHCI1394_CSRControl ; 
 int /*<<< orphan*/  OHCI1394_CSRData ; 
 int OHCI_LOOP_COUNT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int reg_read (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct ti_ohci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static quadlet_t ohci_hw_csr_reg(struct hpsb_host *host, int reg,
                                 quadlet_t data, quadlet_t compare)
{
	struct ti_ohci *ohci = host->hostdata;
	int i;

	reg_write(ohci, OHCI1394_CSRData, data);
	reg_write(ohci, OHCI1394_CSRCompareData, compare);
	reg_write(ohci, OHCI1394_CSRControl, reg & 0x3);

	for (i = 0; i < OHCI_LOOP_COUNT; i++) {
		if (reg_read(ohci, OHCI1394_CSRControl) & 0x80000000)
			break;

		mdelay(1);
	}

	return reg_read(ohci, OHCI1394_CSRData);
}