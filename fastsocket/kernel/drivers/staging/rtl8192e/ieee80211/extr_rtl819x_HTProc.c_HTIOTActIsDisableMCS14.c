#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ bCurrentRT2RTAggregation; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINKSYSWRT330_LINKSYSWRT300_BROADCOM ; 
 int /*<<< orphan*/  UNKNOWN_BORADCOM ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pHTInfo ; 

u8 HTIOTActIsDisableMCS14(struct ieee80211_device* ieee, u8* PeerMacAddr)
{
	u8 ret = 0;
#if 0
	// Apply for 819u only
#if (HAL_CODE_BASE==RTL8192 && DEV_BUS_TYPE==USB_INTERFACE)
	if((memcmp(PeerMacAddr, UNKNOWN_BORADCOM, 3)==0) ||
    		(memcmp(PeerMacAddr, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3)==0)
	    )
	{
		ret = 1;
	}


	if(pHTInfo->bCurrentRT2RTAggregation)
	{
		// The parameter of pHTInfo->bCurrentRT2RTAggregation must be decided previously
		ret = 1;
	}
#endif
#endif
	return ret;
 }