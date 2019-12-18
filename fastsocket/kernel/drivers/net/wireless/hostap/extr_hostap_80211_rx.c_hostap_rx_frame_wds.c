#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ieee80211_hdr {int* addr1; int* addr2; } ;
struct TYPE_8__ {scalar_t__ iw_mode; int wds_type; TYPE_6__* ap; TYPE_1__* dev; int /*<<< orphan*/  bssid; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_9__ {scalar_t__ autom_ap_wds; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
 int /*<<< orphan*/  DEBUG_EXTRA2 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int HOSTAP_WDS_AP_CLIENT ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WDS_ADD ; 
 scalar_t__ hostap_is_sta_assoc (TYPE_6__*,int*) ; 
 int /*<<< orphan*/  hostap_wds_link_oper (TYPE_2__*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* prism2_rx_get_wds (TYPE_2__*,int*) ; 

__attribute__((used)) static int
hostap_rx_frame_wds(local_info_t *local, struct ieee80211_hdr *hdr, u16 fc,
		    struct net_device **wds)
{
	/* FIX: is this really supposed to accept WDS frames only in Master
	 * mode? What about Repeater or Managed with WDS frames? */
	if ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) !=
	    (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS) &&
	    (local->iw_mode != IW_MODE_MASTER || !(fc & IEEE80211_FCTL_TODS)))
		return 0; /* not a WDS frame */

	/* Possible WDS frame: either IEEE 802.11 compliant (if FromDS)
	 * or own non-standard frame with 4th address after payload */
	if (memcmp(hdr->addr1, local->dev->dev_addr, ETH_ALEN) != 0 &&
	    (hdr->addr1[0] != 0xff || hdr->addr1[1] != 0xff ||
	     hdr->addr1[2] != 0xff || hdr->addr1[3] != 0xff ||
	     hdr->addr1[4] != 0xff || hdr->addr1[5] != 0xff)) {
		/* RA (or BSSID) is not ours - drop */
		PDEBUG(DEBUG_EXTRA2, "%s: received WDS frame with "
		       "not own or broadcast %s=%pM\n",
		       local->dev->name,
		       fc & IEEE80211_FCTL_FROMDS ? "RA" : "BSSID",
		       hdr->addr1);
		return -1;
	}

	/* check if the frame came from a registered WDS connection */
	*wds = prism2_rx_get_wds(local, hdr->addr2);
	if (*wds == NULL && fc & IEEE80211_FCTL_FROMDS &&
	    (local->iw_mode != IW_MODE_INFRA ||
	     !(local->wds_type & HOSTAP_WDS_AP_CLIENT) ||
	     memcmp(hdr->addr2, local->bssid, ETH_ALEN) != 0)) {
		/* require that WDS link has been registered with TA or the
		 * frame is from current AP when using 'AP client mode' */
		PDEBUG(DEBUG_EXTRA, "%s: received WDS[4 addr] frame "
		       "from unknown TA=%pM\n",
		       local->dev->name, hdr->addr2);
		if (local->ap && local->ap->autom_ap_wds)
			hostap_wds_link_oper(local, hdr->addr2, WDS_ADD);
		return -1;
	}

	if (*wds && !(fc & IEEE80211_FCTL_FROMDS) && local->ap &&
	    hostap_is_sta_assoc(local->ap, hdr->addr2)) {
		/* STA is actually associated with us even though it has a
		 * registered WDS link. Assume it is in 'AP client' mode.
		 * Since this is a 3-addr frame, assume it is not (bogus) WDS
		 * frame and process it like any normal ToDS frame from
		 * associated STA. */
		*wds = NULL;
	}

	return 0;
}