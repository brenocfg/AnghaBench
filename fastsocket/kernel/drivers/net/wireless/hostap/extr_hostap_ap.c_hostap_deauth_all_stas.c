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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ap_data {scalar_t__ num_sta; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AP ; 
 int ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_REASON_PREV_AUTH_NOT_VALID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  prism2_send_mgmt (struct net_device*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void hostap_deauth_all_stas(struct net_device *dev, struct ap_data *ap,
			    int resend)
{
	u8 addr[ETH_ALEN];
	__le16 resp;
	int i;

	PDEBUG(DEBUG_AP, "%s: Deauthenticate all stations\n", dev->name);
	memset(addr, 0xff, ETH_ALEN);

	resp = cpu_to_le16(WLAN_REASON_PREV_AUTH_NOT_VALID);

	/* deauth message sent; try to resend it few times; the message is
	 * broadcast, so it may be delayed until next DTIM; there is not much
	 * else we can do at this point since the driver is going to be shut
	 * down */
	for (i = 0; i < 5; i++) {
		prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT |
				 IEEE80211_STYPE_DEAUTH,
				 (char *) &resp, 2, addr, 0);

		if (!resend || ap->num_sta <= 0)
			return;

		mdelay(50);
	}
}