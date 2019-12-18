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
struct pm8001_hba_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SAS2_SETTINGS_LOCAL_PHY_0_3_OFFSET ; 
 int SAS2_SETTINGS_LOCAL_PHY_0_3_SHIFT_ADDR ; 
 int SAS2_SETTINGS_LOCAL_PHY_4_7_OFFSET ; 
 int SAS2_SETTINGS_LOCAL_PHY_4_7_SHIFT_ADDR ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int,int) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpi_set_phys_g3_with_ssc(struct pm8001_hba_info *pm8001_ha,
				     u32 SSCbit)
{
	u32 value, offset, i;
	unsigned long flags;

#define SAS2_SETTINGS_LOCAL_PHY_0_3_SHIFT_ADDR 0x00030000
#define SAS2_SETTINGS_LOCAL_PHY_4_7_SHIFT_ADDR 0x00040000
#define SAS2_SETTINGS_LOCAL_PHY_0_3_OFFSET 0x1074
#define SAS2_SETTINGS_LOCAL_PHY_4_7_OFFSET 0x1074
#define PHY_G3_WITHOUT_SSC_BIT_SHIFT 12
#define PHY_G3_WITH_SSC_BIT_SHIFT 13
#define SNW3_PHY_CAPABILITIES_PARITY 31

   /*
    * Using shifted destination address 0x3_0000:0x1074 + 0x4000*N (N=0:3)
    * Using shifted destination address 0x4_0000:0x1074 + 0x4000*(N-4) (N=4:7)
    */
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	if (-1 == pm8001_bar4_shift(pm8001_ha,
				SAS2_SETTINGS_LOCAL_PHY_0_3_SHIFT_ADDR)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		return;
	}

	for (i = 0; i < 4; i++) {
		offset = SAS2_SETTINGS_LOCAL_PHY_0_3_OFFSET + 0x4000 * i;
		pm8001_cw32(pm8001_ha, 2, offset, 0x80001501);
	}
	/* shift membase 3 for SAS2_SETTINGS_LOCAL_PHY 4 - 7 */
	if (-1 == pm8001_bar4_shift(pm8001_ha,
				SAS2_SETTINGS_LOCAL_PHY_4_7_SHIFT_ADDR)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		return;
	}
	for (i = 4; i < 8; i++) {
		offset = SAS2_SETTINGS_LOCAL_PHY_4_7_OFFSET + 0x4000 * (i-4);
		pm8001_cw32(pm8001_ha, 2, offset, 0x80001501);
	}
	/*************************************************************
	Change the SSC upspreading value to 0x0 so that upspreading is disabled.
	Device MABC SMOD0 Controls
	Address: (via MEMBASE-III):
	Using shifted destination address 0x0_0000: with Offset 0xD8

	31:28 R/W Reserved Do not change
	27:24 R/W SAS_SMOD_SPRDUP 0000
	23:20 R/W SAS_SMOD_SPRDDN 0000
	19:0  R/W  Reserved Do not change
	Upon power-up this register will read as 0x8990c016,
	and I would like you to change the SAS_SMOD_SPRDUP bits to 0b0000
	so that the written value will be 0x8090c016.
	This will ensure only down-spreading SSC is enabled on the SPC.
	*************************************************************/
	value = pm8001_cr32(pm8001_ha, 2, 0xd8);
	pm8001_cw32(pm8001_ha, 2, 0xd8, 0x8000C016);

	/*set the shifted destination address to 0x0 to avoid error operation */
	pm8001_bar4_shift(pm8001_ha, 0x0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	return;
}