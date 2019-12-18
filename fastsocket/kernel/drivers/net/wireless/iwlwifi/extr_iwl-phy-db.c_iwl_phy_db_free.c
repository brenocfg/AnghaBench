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
struct iwl_phy_db {int dummy; } ;

/* Variables and functions */
 int IWL_NUM_PAPD_CH_GROUPS ; 
 int IWL_NUM_TXP_CH_GROUPS ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_CH ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_CHG_PAPD ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_CHG_TXP ; 
 int /*<<< orphan*/  IWL_PHY_DB_CALIB_NCH ; 
 int /*<<< orphan*/  IWL_PHY_DB_CFG ; 
 int /*<<< orphan*/  iwl_phy_db_free_section (struct iwl_phy_db*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct iwl_phy_db*) ; 

void iwl_phy_db_free(struct iwl_phy_db *phy_db)
{
	int i;

	if (!phy_db)
		return;

	iwl_phy_db_free_section(phy_db, IWL_PHY_DB_CFG, 0);
	iwl_phy_db_free_section(phy_db, IWL_PHY_DB_CALIB_NCH, 0);
	iwl_phy_db_free_section(phy_db, IWL_PHY_DB_CALIB_CH, 0);
	for (i = 0; i < IWL_NUM_PAPD_CH_GROUPS; i++)
		iwl_phy_db_free_section(phy_db, IWL_PHY_DB_CALIB_CHG_PAPD, i);
	for (i = 0; i < IWL_NUM_TXP_CH_GROUPS; i++)
		iwl_phy_db_free_section(phy_db, IWL_PHY_DB_CALIB_CHG_TXP, i);

	kfree(phy_db);
}