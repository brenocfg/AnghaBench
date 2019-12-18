#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct asd_phy {TYPE_2__* id_frm_tok; TYPE_1__* phy_desc; } ;
struct asd_ha_struct {struct asd_phy* phys; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma_handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy_control_3; int /*<<< orphan*/  phy_control_2; int /*<<< orphan*/  phy_control_1; int /*<<< orphan*/  phy_control_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_COMINIT_TIMEOUT ; 
 int /*<<< orphan*/  HOTPLUG_DELAY_TIMEOUT ; 
 int /*<<< orphan*/  HOT_PLUG_DELAY ; 
 int /*<<< orphan*/  INT_ENABLE_2 ; 
 int /*<<< orphan*/  LmSEQ_OOB_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LmSEQ_TEN_MS_COMINIT_TIMEOUT (int) ; 
 int /*<<< orphan*/  LmSEQ_TX_ID_ADDR_FRAME (int) ; 
 int /*<<< orphan*/  PHY_CONTROL_0 ; 
 int /*<<< orphan*/  PHY_CONTROL_1 ; 
 int /*<<< orphan*/  PHY_CONTROL_2 ; 
 int /*<<< orphan*/  PHY_CONTROL_3 ; 
 int /*<<< orphan*/  asd_control_led (struct asd_ha_struct*,int,int) ; 
 int /*<<< orphan*/  asd_write_reg_addr (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_enable_phy(struct asd_ha_struct *asd_ha, int phy_id)
{
	struct asd_phy *phy = &asd_ha->phys[phy_id];

	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, INT_ENABLE_2), 0);
	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, HOT_PLUG_DELAY),
			   HOTPLUG_DELAY_TIMEOUT);

	/* Get defaults from manuf. sector */
	/* XXX we need defaults for those in case MS is broken. */
	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_0),
			   phy->phy_desc->phy_control_0);
	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_1),
			   phy->phy_desc->phy_control_1);
	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_2),
			   phy->phy_desc->phy_control_2);
	asd_write_reg_byte(asd_ha, LmSEQ_OOB_REG(phy_id, PHY_CONTROL_3),
			   phy->phy_desc->phy_control_3);

	asd_write_reg_dword(asd_ha, LmSEQ_TEN_MS_COMINIT_TIMEOUT(phy_id),
			    ASD_COMINIT_TIMEOUT);

	asd_write_reg_addr(asd_ha, LmSEQ_TX_ID_ADDR_FRAME(phy_id),
			   phy->id_frm_tok->dma_handle);

	asd_control_led(asd_ha, phy_id, 1);

	return 0;
}