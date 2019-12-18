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
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int ErrorOrNot; int Recorver; int /*<<< orphan*/  Value; } ;
typedef  size_t RF90_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 TYPE_1__** RF_Shadow ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern void PHY_RFShadowRecorver(
	struct net_device		* dev,
	RF90_RADIO_PATH_E	eRFPath,
	u32					Offset)
{
	// Check if the address is error
	if (RF_Shadow[eRFPath][Offset].ErrorOrNot == true)
	{
		// Check if we need to recorver the register.
		if (RF_Shadow[eRFPath][Offset].Recorver == true)
		{
			rtl8192_phy_SetRFReg(dev, eRFPath, Offset, bRFRegOffsetMask, RF_Shadow[eRFPath][Offset].Value);
			RT_TRACE(COMP_INIT, "PHY_RFShadowRecorver RF-%d Addr%02x=%05x",
			eRFPath, Offset, RF_Shadow[eRFPath][Offset].Value);
		}
	}

}