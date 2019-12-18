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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mci; } ;
struct ath_softc {int /*<<< orphan*/  mci_work; int /*<<< orphan*/  hw; TYPE_1__ btcoex; struct ath_hw* sc_ah; } ;
struct ath_mci_profile_status {int is_link; int conn_handle; int is_critical; } ;
struct ath_mci_profile_info {int /*<<< orphan*/  start; int /*<<< orphan*/  type; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI ; 
#define  MCI_GPM_COEX_BT_PROFILE_INFO 132 
#define  MCI_GPM_COEX_BT_STATUS_UPDATE 131 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MAJOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MINOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_PROFILE_TYPE ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_STATUS_LINKID ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_STATUS_STATE ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_STATUS_TYPE ; 
 int /*<<< orphan*/  MCI_GPM_COEX_PROFILE_MAX ; 
 int /*<<< orphan*/  MCI_GPM_COEX_PROFILE_UNKNOWN ; 
#define  MCI_GPM_COEX_STATUS_QUERY 130 
#define  MCI_GPM_COEX_VERSION_QUERY 129 
#define  MCI_GPM_COEX_VERSION_RESPONSE 128 
 int /*<<< orphan*/  MCI_STATE_ENABLE ; 
 int /*<<< orphan*/  MCI_STATE_NEED_FLUSH_BT_INFO ; 
 int /*<<< orphan*/  MCI_STATE_SEND_STATUS_QUERY ; 
 int /*<<< orphan*/  MCI_STATE_SEND_WLAN_COEX_VERSION ; 
 int /*<<< orphan*/  ar9003_mci_send_wlan_channels (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_set_bt_version (struct ath_hw*,int,int) ; 
 scalar_t__ ar9003_mci_state (struct ath_hw*,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath_mci_flush_profile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_mci_process_profile (struct ath_softc*,struct ath_mci_profile_info*) ; 
 int /*<<< orphan*/  ath_mci_process_status (struct ath_softc*,struct ath_mci_profile_status*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ath_mci_profile_info*,int*,int) ; 

__attribute__((used)) static void ath_mci_msg(struct ath_softc *sc, u8 opcode, u8 *rx_payload)
{
	struct ath_hw *ah = sc->sc_ah;
	struct ath_mci_profile_info profile_info;
	struct ath_mci_profile_status profile_status;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	u8 major, minor, update_scheme = 0;
	u32 seq_num;

	if (ar9003_mci_state(ah, MCI_STATE_NEED_FLUSH_BT_INFO) &&
	    ar9003_mci_state(ah, MCI_STATE_ENABLE)) {
		ath_dbg(common, MCI, "(MCI) Need to flush BT profiles\n");
		ath_mci_flush_profile(&sc->btcoex.mci);
		ar9003_mci_state(ah, MCI_STATE_SEND_STATUS_QUERY);
	}

	switch (opcode) {
	case MCI_GPM_COEX_VERSION_QUERY:
		ar9003_mci_state(ah, MCI_STATE_SEND_WLAN_COEX_VERSION);
		break;
	case MCI_GPM_COEX_VERSION_RESPONSE:
		major = *(rx_payload + MCI_GPM_COEX_B_MAJOR_VERSION);
		minor = *(rx_payload + MCI_GPM_COEX_B_MINOR_VERSION);
		ar9003_mci_set_bt_version(ah, major, minor);
		break;
	case MCI_GPM_COEX_STATUS_QUERY:
		ar9003_mci_send_wlan_channels(ah);
		break;
	case MCI_GPM_COEX_BT_PROFILE_INFO:
		memcpy(&profile_info,
		       (rx_payload + MCI_GPM_COEX_B_PROFILE_TYPE), 10);

		if ((profile_info.type == MCI_GPM_COEX_PROFILE_UNKNOWN) ||
		    (profile_info.type >= MCI_GPM_COEX_PROFILE_MAX)) {
			ath_dbg(common, MCI,
				"Illegal profile type = %d, state = %d\n",
				profile_info.type,
				profile_info.start);
			break;
		}

		update_scheme += ath_mci_process_profile(sc, &profile_info);
		break;
	case MCI_GPM_COEX_BT_STATUS_UPDATE:
		profile_status.is_link = *(rx_payload +
					   MCI_GPM_COEX_B_STATUS_TYPE);
		profile_status.conn_handle = *(rx_payload +
					       MCI_GPM_COEX_B_STATUS_LINKID);
		profile_status.is_critical = *(rx_payload +
					       MCI_GPM_COEX_B_STATUS_STATE);

		seq_num = *((u32 *)(rx_payload + 12));
		ath_dbg(common, MCI,
			"BT_Status_Update: is_link=%d, linkId=%d, state=%d, SEQ=%u\n",
			profile_status.is_link, profile_status.conn_handle,
			profile_status.is_critical, seq_num);

		update_scheme += ath_mci_process_status(sc, &profile_status);
		break;
	default:
		ath_dbg(common, MCI, "Unknown GPM COEX message = 0x%02x\n", opcode);
		break;
	}
	if (update_scheme)
		ieee80211_queue_work(sc->hw, &sc->mci_work);
}