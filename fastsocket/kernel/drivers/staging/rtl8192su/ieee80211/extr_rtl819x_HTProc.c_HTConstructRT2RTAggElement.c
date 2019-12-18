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
struct ieee80211_device {scalar_t__ bSupportRemoteWakeUp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void HTConstructRT2RTAggElement(struct ieee80211_device* ieee, u8* posRT2RTAgg, u8* len)
{
	if (posRT2RTAgg == NULL) {
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "posRT2RTAgg can't be null in HTConstructRT2RTAggElement()\n");
		return;
	}
	memset(posRT2RTAgg, 0, *len);
	*posRT2RTAgg++ = 0x00;
	*posRT2RTAgg++ = 0xe0;
	*posRT2RTAgg++ = 0x4c;
	*posRT2RTAgg++ = 0x02;
	*posRT2RTAgg++ = 0x01;
	*posRT2RTAgg = 0x10;//*posRT2RTAgg = 0x02;

	if(ieee->bSupportRemoteWakeUp) {
		*posRT2RTAgg |= 0x08;//RT_HT_CAP_USE_WOW;
	}

	*len = 6 + 2;
	return;
#ifdef TODO
#if(HAL_CODE_BASE == RTL8192 && DEV_BUS_TYPE == USB_INTERFACE)
	/*
	//Emily. If it is required to Ask Realtek AP to send AMPDU during AES mode, enable this
	   section of code.
	if(IS_UNDER_11N_AES_MODE(Adapter))
	{
		posRT2RTAgg->Octet[5] |=RT_HT_CAP_USE_AMPDU;
	}else
	{
		posRT2RTAgg->Octet[5] &= 0xfb;
	}
	*/

#else
	// Do Nothing
#endif

	posRT2RTAgg->Length = 6;
#endif




}