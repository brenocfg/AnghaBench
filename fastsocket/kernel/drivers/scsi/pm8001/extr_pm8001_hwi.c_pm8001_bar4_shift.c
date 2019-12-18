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
typedef  scalar_t__ u32 ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPC_IBW_AXI_TRANSLATION_LOW ; 
 unsigned long jiffies ; 
 scalar_t__ pm8001_cr32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pm8001_printk (char*,scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int pm8001_bar4_shift(struct pm8001_hba_info *pm8001_ha, u32 shiftValue)
{
	u32 regVal;
	unsigned long start;

	/* program the inbound AXI translation Lower Address */
	pm8001_cw32(pm8001_ha, 1, SPC_IBW_AXI_TRANSLATION_LOW, shiftValue);

	/* confirm the setting is written */
	start = jiffies + HZ; /* 1 sec */
	do {
		regVal = pm8001_cr32(pm8001_ha, 1, SPC_IBW_AXI_TRANSLATION_LOW);
	} while ((regVal != shiftValue) && time_before(jiffies, start));

	if (regVal != shiftValue) {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("TIMEOUT:SPC_IBW_AXI_TRANSLATION_LOW"
			" = 0x%x\n", regVal));
		return -1;
	}
	return 0;
}