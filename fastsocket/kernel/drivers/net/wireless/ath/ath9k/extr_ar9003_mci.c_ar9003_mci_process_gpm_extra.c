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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ath9k_hw_mci {int bt_version_known; int wlan_channels_update; int query_bt; scalar_t__ bt_ver_minor; scalar_t__ bt_ver_major; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI ; 
 scalar_t__ MCI_GPM_COEX_AGENT ; 
#define  MCI_GPM_COEX_BT_PROFILE_INFO 132 
#define  MCI_GPM_COEX_BT_STATUS_UPDATE 131 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MAJOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MINOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_WLAN_BITMAP ; 
#define  MCI_GPM_COEX_STATUS_QUERY 130 
#define  MCI_GPM_COEX_VERSION_QUERY 129 
#define  MCI_GPM_COEX_VERSION_RESPONSE 128 
 int /*<<< orphan*/  ar9003_mci_send_coex_version_response (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_wlan_channels (struct ath_hw*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void ar9003_mci_process_gpm_extra(struct ath_hw *ah, u8 gpm_type,
					 u8 gpm_opcode, u32 *p_gpm)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u8 *p_data = (u8 *) p_gpm;

	if (gpm_type != MCI_GPM_COEX_AGENT)
		return;

	switch (gpm_opcode) {
	case MCI_GPM_COEX_VERSION_QUERY:
		ath_dbg(common, MCI, "MCI Recv GPM COEX Version Query\n");
		ar9003_mci_send_coex_version_response(ah, true);
		break;
	case MCI_GPM_COEX_VERSION_RESPONSE:
		ath_dbg(common, MCI, "MCI Recv GPM COEX Version Response\n");
		mci->bt_ver_major =
			*(p_data + MCI_GPM_COEX_B_MAJOR_VERSION);
		mci->bt_ver_minor =
			*(p_data + MCI_GPM_COEX_B_MINOR_VERSION);
		mci->bt_version_known = true;
		ath_dbg(common, MCI, "MCI BT Coex version: %d.%d\n",
			mci->bt_ver_major, mci->bt_ver_minor);
		break;
	case MCI_GPM_COEX_STATUS_QUERY:
		ath_dbg(common, MCI,
			"MCI Recv GPM COEX Status Query = 0x%02X\n",
			*(p_data + MCI_GPM_COEX_B_WLAN_BITMAP));
		mci->wlan_channels_update = true;
		ar9003_mci_send_coex_wlan_channels(ah, true);
		break;
	case MCI_GPM_COEX_BT_PROFILE_INFO:
		mci->query_bt = true;
		ath_dbg(common, MCI, "MCI Recv GPM COEX BT_Profile_Info\n");
		break;
	case MCI_GPM_COEX_BT_STATUS_UPDATE:
		mci->query_bt = true;
		ath_dbg(common, MCI,
			"MCI Recv GPM COEX BT_Status_Update SEQ=%d (drop&query)\n",
			*(p_gpm + 3));
		break;
	default:
		break;
	}
}