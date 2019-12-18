#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  numpacket_toself; int /*<<< orphan*/  numpacket_matchbssid; } ;
struct r8192_priv {TYPE_4__ stats; TYPE_3__* ieee80211; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct ieee80211_rx_stats {int /*<<< orphan*/  bICV; int /*<<< orphan*/  bCRC; int /*<<< orphan*/  bHwError; } ;
struct ieee80211_hdr_3addr {int /*<<< orphan*/ * addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/ * addr1; int /*<<< orphan*/  frame_ctl; } ;
typedef  int /*<<< orphan*/  prx_fwinfo_819x_pci ;
typedef  int /*<<< orphan*/  prx_desc_819x_pci ;
struct TYPE_5__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_7__ {TYPE_2__* dev; TYPE_1__ current_network; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_FCTL_FROMDS ; 
 scalar_t__ IEEE80211_FCTL_TODS ; 
 scalar_t__ IEEE80211_FTYPE_CTL ; 
 scalar_t__ IEEE80211_STYPE_BEACON ; 
 scalar_t__ IEEE80211_STYPE_BLOCKACK ; 
 scalar_t__ WLAN_FC_GET_FRAMETYPE (scalar_t__) ; 
 scalar_t__ WLAN_FC_GET_TYPE (scalar_t__) ; 
 int eqMacAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_process_phyinfo (struct r8192_priv*,int /*<<< orphan*/ *,struct ieee80211_rx_stats*,struct ieee80211_rx_stats*) ; 
 int /*<<< orphan*/  rtl8192_query_rxphystatus (struct r8192_priv*,struct ieee80211_rx_stats*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_rx_stats*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl8192_record_rxdesc_forlateruse (struct ieee80211_rx_stats*,struct ieee80211_rx_stats*) ; 

__attribute__((used)) static void TranslateRxSignalStuff819xpci(struct net_device *dev,
        struct sk_buff *skb,
        struct ieee80211_rx_stats * pstats,
        prx_desc_819x_pci pdesc,
        prx_fwinfo_819x_pci pdrvinfo)
{
    // TODO: We must only check packet for current MAC address. Not finish
    struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
    bool bpacket_match_bssid, bpacket_toself;
    bool bPacketBeacon=false, bToSelfBA=false;
    static struct ieee80211_rx_stats  previous_stats;
    struct ieee80211_hdr_3addr *hdr;
    u16 fc,type;

    // Get Signal Quality for only RX data queue (but not command queue)

    u8* tmp_buf;
    u8	*praddr;

    /* Get MAC frame start address. */
    tmp_buf = skb->data;

    hdr = (struct ieee80211_hdr_3addr *)tmp_buf;
    fc = le16_to_cpu(hdr->frame_ctl);
    type = WLAN_FC_GET_TYPE(fc);
    praddr = hdr->addr1;

    /* Check if the received packet is acceptabe. */
    bpacket_match_bssid = ((IEEE80211_FTYPE_CTL != type) &&
            (eqMacAddr(priv->ieee80211->current_network.bssid,	(fc & IEEE80211_FCTL_TODS)? hdr->addr1 : (fc & IEEE80211_FCTL_FROMDS )? hdr->addr2 : hdr->addr3))
            && (!pstats->bHwError) && (!pstats->bCRC)&& (!pstats->bICV));
    bpacket_toself =  bpacket_match_bssid & (eqMacAddr(praddr, priv->ieee80211->dev->dev_addr));
#if 1//cosa
    if(WLAN_FC_GET_FRAMETYPE(fc)== IEEE80211_STYPE_BEACON)
    {
        bPacketBeacon = true;
        //DbgPrint("Beacon 2, MatchBSSID = %d, ToSelf = %d \n", bPacketMatchBSSID, bPacketToSelf);
    }
    if(WLAN_FC_GET_FRAMETYPE(fc) == IEEE80211_STYPE_BLOCKACK)
    {
        if((eqMacAddr(praddr,dev->dev_addr)))
            bToSelfBA = true;
        //DbgPrint("BlockAck, MatchBSSID = %d, ToSelf = %d \n", bPacketMatchBSSID, bPacketToSelf);
    }

#endif
    if(bpacket_match_bssid)
    {
        priv->stats.numpacket_matchbssid++;
    }
    if(bpacket_toself){
        priv->stats.numpacket_toself++;
    }
    //
    // Process PHY information for previous packet (RSSI/PWDB/EVM)
    //
    // Because phy information is contained in the last packet of AMPDU only, so driver
    // should process phy information of previous packet
    rtl8192_process_phyinfo(priv, tmp_buf,&previous_stats, pstats);
    rtl8192_query_rxphystatus(priv, pstats, pdesc, pdrvinfo, &previous_stats, bpacket_match_bssid,
            bpacket_toself ,bPacketBeacon, bToSelfBA);
    rtl8192_record_rxdesc_forlateruse(pstats, &previous_stats);

}