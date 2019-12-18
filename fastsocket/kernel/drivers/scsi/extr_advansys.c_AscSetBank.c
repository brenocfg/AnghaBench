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
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int AscGetChipControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipControl (int /*<<< orphan*/ ,int) ; 
 int CC_BANK_ONE ; 
 int CC_CHIP_RESET ; 
 int CC_DIAG ; 
 int CC_SCSI_RESET ; 
 int CC_SINGLE_STEP ; 
 int CC_TEST ; 

__attribute__((used)) static void AscSetBank(PortAddr iop_base, uchar bank)
{
	uchar val;

	val = AscGetChipControl(iop_base) &
	    (~
	     (CC_SINGLE_STEP | CC_TEST | CC_DIAG | CC_SCSI_RESET |
	      CC_CHIP_RESET));
	if (bank == 1) {
		val |= CC_BANK_ONE;
	} else if (bank == 2) {
		val |= CC_DIAG | CC_BANK_ONE;
	} else {
		val &= ~CC_BANK_ONE;
	}
	AscSetChipControl(iop_base, val);
}