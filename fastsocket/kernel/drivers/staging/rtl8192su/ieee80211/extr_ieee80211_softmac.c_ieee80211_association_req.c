#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_13__ {scalar_t__ supported; } ;
struct ieee80211_network {int BssCcxVerNumber; int ssid_len; int* bssid; int capability; int* ssid; scalar_t__ bCcxRmEnable; scalar_t__ bCkipSupported; TYPE_6__ qos_data; scalar_t__ Turbo_Enable; } ;
struct ieee80211_device {int wpa_ie_len; size_t tx_keyidx; int tx_headroom; int* ap_mac_addr; int* wpa_ie; TYPE_5__* pHTInfo; scalar_t__ short_slot; TYPE_1__* dev; scalar_t__ qos_support; scalar_t__ host_encrypt; struct ieee80211_crypt_data** crypt; } ;
struct ieee80211_crypt_data {TYPE_4__* ops; } ;
struct TYPE_9__ {int duration_id; int* addr1; int* addr2; int* addr3; int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_assoc_request_frame {int listen_interval; TYPE_3__* info_element; int /*<<< orphan*/  capability; TYPE_2__ header; } ;
struct TYPE_14__ {int* Octet; int Length; } ;
struct TYPE_12__ {int* szRT2RTAggBuffer; scalar_t__ ePeerHTSpecVer; scalar_t__ bCurrentRT2RTAggregation; scalar_t__ bEnableHT; scalar_t__ bCurrentHTSupport; int /*<<< orphan*/  SelfHTCap; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int len; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int* dev_addr; } ;
typedef  TYPE_7__ OCTET_STRING ;
typedef  int /*<<< orphan*/  CcxVerNumBuf ;
typedef  int /*<<< orphan*/  CcxRmCapBuf ;
typedef  int /*<<< orphan*/  CcxAironetBuf ;
typedef  int /*<<< orphan*/  AironetIeOui ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  HTConstructCapabilityElement (struct ieee80211_device*,int*,int*,int) ; 
 int /*<<< orphan*/  HTConstructRT2RTAggElement (struct ieee80211_device*,int*,int*) ; 
 scalar_t__ HT_SPEC_VER_EWC ; 
 int /*<<< orphan*/  IEEE80211_STYPE_ASSOC_REQ ; 
 size_t IE_CISCO_FLAG_POSITION ; 
 int /*<<< orphan*/  MFIE_TYPE_AIRONET ; 
 void* MFIE_TYPE_GENERIC ; 
 int /*<<< orphan*/  MFIE_TYPE_HT_CAP ; 
 int /*<<< orphan*/  MFIE_TYPE_SSID ; 
 int SUPPORT_CKIP_MIC ; 
 int SUPPORT_CKIP_PK ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_PRIVACY ; 
 int WLAN_CAPABILITY_QOS ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int WLAN_CAPABILITY_SHORT_SLOT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Brate (struct ieee80211_device*,int**) ; 
 int /*<<< orphan*/  ieee80211_MFIE_Grate (struct ieee80211_device*,int**) ; 
 unsigned int ieee80211_MFIE_rate_len (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_TURBO_Info (struct ieee80211_device*,int**) ; 
 int /*<<< orphan*/  ieee80211_WMM_Info (struct ieee80211_device*,int**) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

inline struct sk_buff *ieee80211_association_req(struct ieee80211_network *beacon,struct ieee80211_device *ieee)
{
	struct sk_buff *skb;
	//unsigned long flags;

	struct ieee80211_assoc_request_frame *hdr;
	u8 *tag;//,*rsn_ie;
	//short info_addr = 0;
	//int i;
	//u16 suite_count = 0;
	//u8 suit_select = 0;
	//unsigned int wpa_len = beacon->wpa_ie_len;
	//for HT
	u8* ht_cap_buf = NULL;
	u8 ht_cap_len=0;
	u8* realtek_ie_buf=NULL;
	u8 realtek_ie_len=0;
	int wpa_ie_len= ieee->wpa_ie_len;
	unsigned int ckip_ie_len=0;
	unsigned int ccxrm_ie_len=0;
	unsigned int cxvernum_ie_len=0;
	struct ieee80211_crypt_data* crypt;
	int encrypt;

	unsigned int rate_len = ieee80211_MFIE_rate_len(ieee);
	unsigned int wmm_info_len = beacon->qos_data.supported?9:0;
	unsigned int turbo_info_len = beacon->Turbo_Enable?9:0;

	int len = 0;

	crypt = ieee->crypt[ieee->tx_keyidx];
	encrypt = ieee->host_encrypt && crypt && crypt->ops && ((0 == strcmp(crypt->ops->name,"WEP") || wpa_ie_len));

	//Include High Throuput capability && Realtek proprietary
	if(ieee->pHTInfo->bCurrentHTSupport&&ieee->pHTInfo->bEnableHT)
	{
		ht_cap_buf = (u8*)&(ieee->pHTInfo->SelfHTCap);
		ht_cap_len = sizeof(ieee->pHTInfo->SelfHTCap);
		HTConstructCapabilityElement(ieee, ht_cap_buf, &ht_cap_len, encrypt);
		if(ieee->pHTInfo->bCurrentRT2RTAggregation)
		{
			realtek_ie_buf = ieee->pHTInfo->szRT2RTAggBuffer;
			realtek_ie_len = sizeof( ieee->pHTInfo->szRT2RTAggBuffer);
			HTConstructRT2RTAggElement(ieee, realtek_ie_buf, &realtek_ie_len);

		}
	}
	if(ieee->qos_support){
		wmm_info_len = beacon->qos_data.supported?9:0;
	}


	if(beacon->bCkipSupported)
	{
		ckip_ie_len = 30+2;
	}
	if(beacon->bCcxRmEnable)
	{
		ccxrm_ie_len = 6+2;
	}
	if( beacon->BssCcxVerNumber >= 2 )
	{
		cxvernum_ie_len = 5+2;
	}
	len = sizeof(struct ieee80211_assoc_request_frame)+ 2
		+ beacon->ssid_len//essid tagged val
		+ rate_len//rates tagged val
		+ wpa_ie_len
		+ wmm_info_len
		+ turbo_info_len
                + ht_cap_len
		+ realtek_ie_len
		+ ckip_ie_len
		+ ccxrm_ie_len
		+ cxvernum_ie_len
		+ ieee->tx_headroom;

	skb = dev_alloc_skb(len);

	if (!skb)
		return NULL;

	skb_reserve(skb, ieee->tx_headroom);

	hdr = (struct ieee80211_assoc_request_frame *)
		skb_put(skb, sizeof(struct ieee80211_assoc_request_frame)+2);


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
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_PREAMBLE); //add short_preamble here

	if(ieee->short_slot)
		hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_SHORT_SLOT);
 	if (wmm_info_len) //QOS
	hdr->capability |= cpu_to_le16(WLAN_CAPABILITY_QOS);

	hdr->listen_interval = 0xa; //FIXME

	hdr->info_element[0].id = MFIE_TYPE_SSID;

	hdr->info_element[0].len = beacon->ssid_len;
	tag = skb_put(skb, beacon->ssid_len);
	memcpy(tag, beacon->ssid, beacon->ssid_len);

	tag = skb_put(skb, rate_len);

	ieee80211_MFIE_Brate(ieee, &tag);
	ieee80211_MFIE_Grate(ieee, &tag);
	// For CCX 1 S13, CKIP. Added by Annie, 2006-08-14.
	if( beacon->bCkipSupported )
	{
		static u8	AironetIeOui[] = {0x00, 0x01, 0x66}; // "4500-client"
		u8	CcxAironetBuf[30];
		OCTET_STRING	osCcxAironetIE;

		memset(CcxAironetBuf, 0,30);
		osCcxAironetIE.Octet = CcxAironetBuf;
		osCcxAironetIE.Length = sizeof(CcxAironetBuf);
		//
		// Ref. CCX test plan v3.61, 3.2.3.1 step 13.
		// We want to make the device type as "4500-client". 060926, by CCW.
		//
		memcpy(osCcxAironetIE.Octet, AironetIeOui, sizeof(AironetIeOui));

		// CCX1 spec V1.13, A01.1 CKIP Negotiation (page23):
		// "The CKIP negotiation is started with the associate request from the client to the access point,
		//  containing an Aironet element with both the MIC and KP bits set."
		osCcxAironetIE.Octet[IE_CISCO_FLAG_POSITION] |=  (SUPPORT_CKIP_PK|SUPPORT_CKIP_MIC) ;
		tag = skb_put(skb, ckip_ie_len);
		*tag++ = MFIE_TYPE_AIRONET;
		*tag++ = osCcxAironetIE.Length;
		memcpy(tag,osCcxAironetIE.Octet,osCcxAironetIE.Length);
		tag += osCcxAironetIE.Length;
	}

	if(beacon->bCcxRmEnable)
	{
		static u8 CcxRmCapBuf[] = {0x00, 0x40, 0x96, 0x01, 0x01, 0x00};
		OCTET_STRING osCcxRmCap;

		osCcxRmCap.Octet = CcxRmCapBuf;
		osCcxRmCap.Length = sizeof(CcxRmCapBuf);
		tag = skb_put(skb,ccxrm_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxRmCap.Length;
		memcpy(tag,osCcxRmCap.Octet,osCcxRmCap.Length);
		tag += osCcxRmCap.Length;
	}

	if( beacon->BssCcxVerNumber >= 2 )
	{
		u8			CcxVerNumBuf[] = {0x00, 0x40, 0x96, 0x03, 0x00};
		OCTET_STRING	osCcxVerNum;
		CcxVerNumBuf[4] = beacon->BssCcxVerNumber;
		osCcxVerNum.Octet = CcxVerNumBuf;
		osCcxVerNum.Length = sizeof(CcxVerNumBuf);
		tag = skb_put(skb,cxvernum_ie_len);
		*tag++ = MFIE_TYPE_GENERIC;
		*tag++ = osCcxVerNum.Length;
		memcpy(tag,osCcxVerNum.Octet,osCcxVerNum.Length);
		tag += osCcxVerNum.Length;
	}
        //HT cap element
	if(ieee->pHTInfo->bCurrentHTSupport&&ieee->pHTInfo->bEnableHT){
		if(ieee->pHTInfo->ePeerHTSpecVer != HT_SPEC_VER_EWC)
		{
			tag = skb_put(skb, ht_cap_len);
			*tag++ = MFIE_TYPE_HT_CAP;
			*tag++ = ht_cap_len - 2;
			memcpy(tag, ht_cap_buf,ht_cap_len -2);
			tag += ht_cap_len -2;
		}
	}


	//choose what wpa_supplicant gives to associate.
	tag = skb_put(skb, wpa_ie_len);
	if (wpa_ie_len){
		memcpy(tag, ieee->wpa_ie, ieee->wpa_ie_len);
	}

	tag = skb_put(skb,wmm_info_len);
	if(wmm_info_len) {
	  ieee80211_WMM_Info(ieee, &tag);
	}
	tag = skb_put(skb,turbo_info_len);
        if(turbo_info_len) {
                ieee80211_TURBO_Info(ieee, &tag);
        }

	if(ieee->pHTInfo->bCurrentHTSupport&&ieee->pHTInfo->bEnableHT){
		if(ieee->pHTInfo->ePeerHTSpecVer == HT_SPEC_VER_EWC)
		{
			tag = skb_put(skb, ht_cap_len);
			*tag++ = MFIE_TYPE_GENERIC;
			*tag++ = ht_cap_len - 2;
			memcpy(tag, ht_cap_buf,ht_cap_len - 2);
			tag += ht_cap_len -2;
		}

		if(ieee->pHTInfo->bCurrentRT2RTAggregation){
			tag = skb_put(skb, realtek_ie_len);
			*tag++ = MFIE_TYPE_GENERIC;
			*tag++ = realtek_ie_len - 2;
			memcpy(tag, realtek_ie_buf,realtek_ie_len -2 );
		}
	}
//	printk("<=====%s(), %p, %p\n", __FUNCTION__, ieee->dev, ieee->dev->dev_addr);
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, skb->data, skb->len);
	return skb;
}