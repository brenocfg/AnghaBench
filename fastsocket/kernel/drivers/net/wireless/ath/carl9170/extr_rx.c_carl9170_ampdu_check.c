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
typedef  int u8 ;
struct ieee80211_rx_status {int flag; int /*<<< orphan*/  ampdu_reference; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ar9170 {int /*<<< orphan*/  ampdu_ref; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int AR9170_RX_STATUS_MPDU ; 
 int AR9170_RX_STATUS_MPDU_SINGLE ; 
 int RX_FLAG_AMPDU_DETAILS ; 
 int RX_FLAG_AMPDU_LAST_KNOWN ; 
 scalar_t__ ieee80211_is_ack (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_back (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool carl9170_ampdu_check(struct ar9170 *ar, u8 *buf, u8 ms,
				 struct ieee80211_rx_status *rx_status)
{
	__le16 fc;

	if ((ms & AR9170_RX_STATUS_MPDU) == AR9170_RX_STATUS_MPDU_SINGLE) {
		/*
		 * This frame is not part of an aMPDU.
		 * Therefore it is not subjected to any
		 * of the following content restrictions.
		 */
		return true;
	}

	rx_status->flag |= RX_FLAG_AMPDU_DETAILS | RX_FLAG_AMPDU_LAST_KNOWN;
	rx_status->ampdu_reference = ar->ampdu_ref;

	/*
	 * "802.11n - 7.4a.3 A-MPDU contents" describes in which contexts
	 * certain frame types can be part of an aMPDU.
	 *
	 * In order to keep the processing cost down, I opted for a
	 * stateless filter solely based on the frame control field.
	 */

	fc = ((struct ieee80211_hdr *)buf)->frame_control;
	if (ieee80211_is_data_qos(fc) && ieee80211_is_data_present(fc))
		return true;

	if (ieee80211_is_ack(fc) || ieee80211_is_back(fc) ||
	    ieee80211_is_back_req(fc))
		return true;

	if (ieee80211_is_action(fc))
		return true;

	return false;
}