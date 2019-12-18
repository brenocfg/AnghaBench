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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_2 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_3 ; 
 int SCRATCH_PAD1_ERR ; 
 int SCRATCH_PAD1_RDY ; 
 int SCRATCH_PAD1_STATE_MASK ; 
 int SCRATCH_PAD2_ERR ; 
 int SCRATCH_PAD2_RDY ; 
 int SCRATCH_PAD2_STATE_MASK ; 
 int SCRATCH_PAD_STATE_MASK ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int check_fw_ready(struct pm8001_hba_info *pm8001_ha)
{
	u32 value, value1;
	u32 max_wait_count;
	/* check error state */
	value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
	value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
	/* check AAP error */
	if (SCRATCH_PAD1_ERR == (value & SCRATCH_PAD_STATE_MASK)) {
		/* error state */
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
		return -1;
	}

	/* check IOP error */
	if (SCRATCH_PAD2_ERR == (value1 & SCRATCH_PAD_STATE_MASK)) {
		/* error state */
		value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3);
		return -1;
	}

	/* bit 4-31 of scratch pad1 should be zeros if it is not
	in error state*/
	if (value & SCRATCH_PAD1_STATE_MASK) {
		/* error case */
		pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0);
		return -1;
	}

	/* bit 2, 4-31 of scratch pad2 should be zeros if it is not
	in error state */
	if (value1 & SCRATCH_PAD2_STATE_MASK) {
		/* error case */
		return -1;
	}

	max_wait_count = 1 * 1000 * 1000;/* 1 sec timeout */

	/* wait until scratch pad 1 and 2 registers in ready state  */
	do {
		udelay(1);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1)
			& SCRATCH_PAD1_RDY;
		value1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2)
			& SCRATCH_PAD2_RDY;
		if ((--max_wait_count) == 0)
			return -1;
	} while ((value != SCRATCH_PAD1_RDY) || (value1 != SCRATCH_PAD2_RDY));
	return 0;
}