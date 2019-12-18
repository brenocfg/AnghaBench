#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_network {unsigned int wpa_ie_len; unsigned int rsn_ie_len; int ssid_len; int capability; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; scalar_t__ Turbo_Enable; scalar_t__ QoS_Enable; } ;
struct ieee80211_device {int wpax_type_notify; scalar_t__* ap_mac_addr; unsigned int wpa_ie_len; int /*<<< orphan*/  wpa_ie; scalar_t__ short_slot; TYPE_1__* dev; scalar_t__ wpax_type_set; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int duration_id; scalar_t__* addr1; scalar_t__* addr2; scalar_t__* addr3; int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_assoc_request_frame {int listen_interval; TYPE_3__ info_element; int /*<<< orphan*/  capability; TYPE_2__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 unsigned int ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_ASSOC_REQ ; 
 scalar_t__ IEEE_PROTO_RSN ; 
 scalar_t__ IEEE_PROTO_WPA ; 
 int /*<<< orphan*/  MFIE_TYPE_SSID ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_SHORT_SLOT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Brate (struct ieee80211_device*,scalar_t__**) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Grate (struct ieee80211_device*,scalar_t__**) ; 
 unsigned int ieee80211_MFIE_rate_len (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_TURBO_Info (struct ieee80211_device*,scalar_t__**) ; 
 int /*<<< orphan*/  ieee80211_WMM_Info (struct ieee80211_device*,scalar_t__**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__* skb_put (struct sk_buff*,unsigned int) ; 

inline struct sk_buff *ieee80211_association_req(struct ieee80211_network *beacon,struct ieee80211_device *ieee)
{
	struct sk_buff *skb;
	//unsigned long flags;

	struct ieee80211_assoc_request_frame *hdr;
	u8 *tag;
	//short info_addr = 0;
	//int i;
	//u16 suite_count = 0;
	//u8 suit_select = 0;
	unsigned int wpa_len = beacon->wpa_ie_len;
	//struct net_device *dev = ieee->dev;
	//union iwreq_data wrqu;
	//u8 *buff;
	//u8 *p;
#if 1
	// for testing purpose
	unsigned int rsn_len = beacon->rsn_ie_len;
#else
	unsigned int rsn_len = beacon->rsn_ie_len - 4;
#endif
	unsigned int rate_len = ieee80211_MFIE_rate_len(ieee);
	unsigned int wmm_info_len = beacon->QoS_Enable?9:0;
	unsigned int turbo_info_len = beacon->Turbo_Enable?9:0;

	u8  encry_proto = ieee->wpax_type_notify & 0xff;
	//u8  pairwise_type = (ieee->wpax_type_notify >> 8) & 0xff;
	//u8  authen_type = (ieee->wpax_type_notify >> 16) & 0xff;

	int len = 0;

	//[0] Notify type of encryption: WPA/WPA2
	//[1] pair wise type
	//[2] authen type
	if(ieee->wpax_type_set) {
		if (IEEE_PROTO_WPA == encry_proto) {
			rsn_len = 0;
		} else if (IEEE_PROTO_RSN == encry_proto) {
			wpa_len = 0;
		}
	}
	len = sizeof(struct ieee80211_assoc_request_frame)+
		+ beacon->ssid_len//essid tagged val
		+ rate_len//rates tagged val
		+ wpa_len
		+ rsn_len
		+ wmm_info_len
		+ turbo_info_len;

	skb = dev_alloc_skb(len);

	if (!skb)
		return NULL;

	hdr = (struct ieee80211_assoc_request_frame *)
		skb_put(skb, sizeof(struct ieee80211_assoc_request_frame));


	hdr->header.frame_ctl = IEEE80211_STYPE_ASSOC_REQ;
	hdr->header.duration_id= 37; //FIXME
	memcpy(hdr->header.addr1, beacon->bssid, ETH_ALEN);
	memcpy(hdr->header.addr2, ieee->dev->dev_addr, ETH_ALEN);
	memcpy(hdr->header.addr3, beacon->bssid, ETH_ALEN);
	memcpy(ieee->ap_mac_addr, beacon->bssid, ETH_ALEN);//for HW security, John

	hdr->capability = cpu_to_le16(WLAN_CAPABILITY_BSS);
	if (beacon->capability & WLAN_CAPABILITY_PRIVACY )
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_PRIVACY);
	if (beacon->capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE);

	if(ieee->short_slot)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT);

	hdr->listen_interval = 0xa; //FIXME

	hdr->info_element.id = MFIE_TYPE_SSID;

	hdr->info_element.len = beacon->ssid_len;
	tag = skb_put(skb, beacon->ssid_len);
	memcpy(tag, beacon->ssid, beacon->ssid_len);

	tag = skb_put(skb, rate_len);

	ieee80211_MFIE_Brate(ieee, &tag);
	ieee80211_MFIE_Grate(ieee, &tag);

	//add rsn==0 condition for ap's mix security mode(wpa+wpa2), john2007.8.9
	//choose AES encryption as default algorithm while using mixed mode

	tag = skb_put(skb,ieee->wpa_ie_len);
	memcpy(tag,ieee->wpa_ie,ieee->wpa_ie_len);

	tag = skb_put(skb,wmm_info_len);
	if(wmm_info_len) {
	  ieee80211_WMM_Info(ieee, &tag);
	}
	tag = skb_put(skb,turbo_info_len);
        if(turbo_info_len) {
                ieee80211_TURBO_Info(ieee, &tag);
        }

	return skb;
}