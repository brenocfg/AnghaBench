#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int hostwep; scalar_t__ priv; } ;
typedef  TYPE_2__ wlandevice_t ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  p80211_metawep_t ;
struct TYPE_7__ {int /*<<< orphan*/  fc; } ;
struct TYPE_9__ {TYPE_1__ a3; } ;
typedef  TYPE_3__ p80211_hdr_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int HOSTWEP_ENCRYPT ; 
 int HOSTWEP_PRIVACYINVOKED ; 
 int /*<<< orphan*/  WLAN_SET_FC_ISWEP (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hfa384x_drvr_txframe (int /*<<< orphan*/ *,struct sk_buff*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prism2sta_txframe(wlandevice_t *wlandev, struct sk_buff *skb,
			     p80211_hdr_t *p80211_hdr,
			     p80211_metawep_t *p80211_wep)
{
	hfa384x_t *hw = (hfa384x_t *) wlandev->priv;
	int result;

	/* If necessary, set the 802.11 WEP bit */
	if ((wlandev->hostwep & (HOSTWEP_PRIVACYINVOKED | HOSTWEP_ENCRYPT)) ==
	    HOSTWEP_PRIVACYINVOKED) {
		p80211_hdr->a3.fc |= cpu_to_le16(WLAN_SET_FC_ISWEP(1));
	}

	result = hfa384x_drvr_txframe(hw, skb, p80211_hdr, p80211_wep);

	return result;
}