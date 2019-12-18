#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cmd; } ;
struct iwl_rx_packet {TYPE_1__ hdr; } ;
struct iwl_phy_db {int dummy; } ;
struct iwl_notif_wait_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ CALIB_RES_NOTIF_PHY_DB ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ INIT_COMPLETE_NOTIF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int iwl_phy_db_set_section (struct iwl_phy_db*,struct iwl_rx_packet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool iwl_wait_phy_db_entry(struct iwl_notif_wait_data *notif_wait,
				  struct iwl_rx_packet *pkt, void *data)
{
	struct iwl_phy_db *phy_db = data;

	if (pkt->hdr.cmd != CALIB_RES_NOTIF_PHY_DB) {
		WARN_ON(pkt->hdr.cmd != INIT_COMPLETE_NOTIF);
		return true;
	}

	WARN_ON(iwl_phy_db_set_section(phy_db, pkt, GFP_ATOMIC));

	return false;
}