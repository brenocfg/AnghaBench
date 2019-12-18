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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  BELKINF5D8233V1_RALINK ; 
 int /*<<< orphan*/  EDIMAX_RALINK ; 
 scalar_t__ IS_UNDER_11N_AES_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_RALINK ; 
 scalar_t__ PlatformCompareMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool HTIOTActIsDisableMCSTwoSpatialStream(struct ieee80211_device* ieee, u8 *PeerMacAddr)
{
	bool retValue = false;

#ifdef TODO
	// Apply for 819u only
//#if (HAL_CODE_BASE==RTL8192)

	//This rule only apply to Belkin(Ralink) AP
	if(IS_UNDER_11N_AES_MODE(Adapter))
	{
		if((PlatformCompareMemory(PeerMacAddr, BELKINF5D8233V1_RALINK, 3)==0) ||
				(PlatformCompareMemory(PeerMacAddr, PCI_RALINK, 3)==0) ||
				(PlatformCompareMemory(PeerMacAddr, EDIMAX_RALINK, 3)==0))
		{
			//Set True to disable this function. Disable by default, Emily, 2008.04.23
			retValue = false;
		}
	}

//#endif
#endif
	return retValue;
}