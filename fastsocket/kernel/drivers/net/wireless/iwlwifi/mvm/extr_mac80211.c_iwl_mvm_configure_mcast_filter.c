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
struct iwl_mvm {int dummy; } ;
struct iwl_mcast_filter_cmd {int pass_all; int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
typedef  int /*<<< orphan*/  mcast_filter_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MCAST_FILTER_CMD ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_mcast_filter_cmd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_configure_mcast_filter(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif)
{
	struct iwl_mcast_filter_cmd mcast_filter_cmd = {
		.pass_all = 1,
	};

	memcpy(mcast_filter_cmd.bssid, vif->bss_conf.bssid, ETH_ALEN);

	return iwl_mvm_send_cmd_pdu(mvm, MCAST_FILTER_CMD, CMD_SYNC,
				    sizeof(mcast_filter_cmd),
				    &mcast_filter_cmd);
}