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
struct iwl_mvm {int dummy; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_WEP (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int RX_MPDU_RES_STATUS_ICV_OK ; 
 int RX_MPDU_RES_STATUS_MIC_OK ; 
#define  RX_MPDU_RES_STATUS_SEC_CCM_ENC 130 
 int RX_MPDU_RES_STATUS_SEC_ENC_ERR ; 
 int RX_MPDU_RES_STATUS_SEC_ENC_MSK ; 
 int RX_MPDU_RES_STATUS_SEC_NO_ENC ; 
#define  RX_MPDU_RES_STATUS_SEC_TKIP_ENC 129 
#define  RX_MPDU_RES_STATUS_SEC_WEP_ENC 128 
 int RX_MPDU_RES_STATUS_TTAK_OK ; 
 int /*<<< orphan*/  ieee80211_has_protected (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_mvm_set_mac80211_rx_flag(struct iwl_mvm *mvm,
					struct ieee80211_hdr *hdr,
					struct ieee80211_rx_status *stats,
					u32 rx_pkt_status)
{
	if (!ieee80211_has_protected(hdr->frame_control) ||
	    (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
			     RX_MPDU_RES_STATUS_SEC_NO_ENC)
		return 0;

	/* packet was encrypted with unknown alg */
	if ((rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
					RX_MPDU_RES_STATUS_SEC_ENC_ERR)
		return 0;

	switch (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) {
	case RX_MPDU_RES_STATUS_SEC_CCM_ENC:
		/* alg is CCM: check MIC only */
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_MIC_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		IWL_DEBUG_WEP(mvm, "hw decrypted CCMP successfully\n");
		return 0;

	case RX_MPDU_RES_STATUS_SEC_TKIP_ENC:
		/* Don't drop the frame and decrypt it in SW */
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_TTAK_OK))
			return 0;
		/* fall through if TTAK OK */

	case RX_MPDU_RES_STATUS_SEC_WEP_ENC:
		if (!(rx_pkt_status & RX_MPDU_RES_STATUS_ICV_OK))
			return -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		return 0;

	default:
		IWL_ERR(mvm, "Unhandled alg: 0x%x\n", rx_pkt_status);
	}

	return 0;
}