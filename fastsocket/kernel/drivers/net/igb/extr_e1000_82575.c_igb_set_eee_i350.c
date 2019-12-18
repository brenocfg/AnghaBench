#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  eee_disable; } ;
struct TYPE_7__ {TYPE_2__ _82575; } ;
struct TYPE_5__ {scalar_t__ media_type; } ;
struct TYPE_8__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ dev_spec; TYPE_1__ phy; TYPE_4__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EEER ; 
 int E1000_EEER_LPI_FC ; 
 int E1000_EEER_RX_LPI_EN ; 
 int E1000_EEER_TX_LPI_EN ; 
 int /*<<< orphan*/  E1000_EEE_SU ; 
 int E1000_EEE_SU_LPI_CLK_STP ; 
 int /*<<< orphan*/  E1000_IPCNFG ; 
 int E1000_IPCNFG_EEE_100M_AN ; 
 int E1000_IPCNFG_EEE_1G_AN ; 
 scalar_t__ e1000_i350 ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igb_set_eee_i350(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u32 ipcnfg, eeer;

	if ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_copper))
		goto out;
	ipcnfg = rd32(E1000_IPCNFG);
	eeer = rd32(E1000_EEER);

	/* enable or disable per user setting */
	if (!(hw->dev_spec._82575.eee_disable)) {
		u32 eee_su = rd32(E1000_EEE_SU);

		ipcnfg |= (E1000_IPCNFG_EEE_1G_AN | E1000_IPCNFG_EEE_100M_AN);
		eeer |= (E1000_EEER_TX_LPI_EN | E1000_EEER_RX_LPI_EN |
			E1000_EEER_LPI_FC);

		/* This bit should not be set in normal operation. */
		if (eee_su & E1000_EEE_SU_LPI_CLK_STP)
			hw_dbg("LPI Clock Stop Bit should not be set!\n");

	} else {
		ipcnfg &= ~(E1000_IPCNFG_EEE_1G_AN |
			E1000_IPCNFG_EEE_100M_AN);
		eeer &= ~(E1000_EEER_TX_LPI_EN |
			E1000_EEER_RX_LPI_EN |
			E1000_EEER_LPI_FC);
	}
	wr32(E1000_IPCNFG, ipcnfg);
	wr32(E1000_EEER, eeer);
	rd32(E1000_IPCNFG);
	rd32(E1000_EEER);
out:

	return ret_val;
}