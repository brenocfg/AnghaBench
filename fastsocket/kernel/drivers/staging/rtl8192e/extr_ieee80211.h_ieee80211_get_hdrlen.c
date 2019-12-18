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
typedef  int u16 ;

/* Variables and functions */
 int IEEE80211_1ADDR_LEN ; 
 int IEEE80211_2ADDR_LEN ; 
 int IEEE80211_3ADDR_LEN ; 
 int IEEE80211_4ADDR_LEN ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
#define  IEEE80211_FTYPE_CTL 131 
#define  IEEE80211_FTYPE_DATA 130 
 int /*<<< orphan*/  IEEE80211_QOS_HAS_SEQ (int) ; 
#define  IEEE80211_STYPE_ACK 129 
#define  IEEE80211_STYPE_CTS 128 
 int /*<<< orphan*/  WLAN_FC_GET_STYPE (int) ; 
 int WLAN_FC_GET_TYPE (int) ; 

extern inline int ieee80211_get_hdrlen(u16 fc)
{
	int hdrlen = IEEE80211_3ADDR_LEN;

	switch (WLAN_FC_GET_TYPE(fc)) {
	case IEEE80211_FTYPE_DATA:
		if ((fc & IEEE80211_FCTL_FROMDS) && (fc & IEEE80211_FCTL_TODS))
			hdrlen = IEEE80211_4ADDR_LEN; /* Addr4 */
		if(IEEE80211_QOS_HAS_SEQ(fc))
			hdrlen += 2; /* QOS ctrl*/
		break;
	case IEEE80211_FTYPE_CTL:
		switch (WLAN_FC_GET_STYPE(fc)) {
		case IEEE80211_STYPE_CTS:
		case IEEE80211_STYPE_ACK:
			hdrlen = IEEE80211_1ADDR_LEN;
			break;
		default:
			hdrlen = IEEE80211_2ADDR_LEN;
			break;
		}
		break;
	}

	return hdrlen;
}