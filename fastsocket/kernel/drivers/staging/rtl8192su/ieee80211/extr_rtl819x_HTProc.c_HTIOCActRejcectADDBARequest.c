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
struct ieee80211_network {int dummy; } ;

/* Variables and functions */

u8
HTIOCActRejcectADDBARequest(struct ieee80211_network *network)
{
	u8	retValue = 0;
	//if(IS_HARDWARE_TYPE_8192SE(Adapter) ||
	//	IS_HARDWARE_TYPE_8192SU(Adapter)
	//)
	{
		// Do not reject ADDBA REQ because some of the AP may
		// keep on sending ADDBA REQ qhich cause DHCP fail or ping loss!
		// by HPFan, 2008/12/30

		//if(pBssDesc->Vender == HT_IOT_PEER_MARVELL)
		//	return FALSE;

	}

	return retValue;

}