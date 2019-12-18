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
struct TYPE_2__ {int Compare; size_t Value; int ErrorOrNot; } ;
typedef  size_t RF90_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 TYPE_1__** RF_Shadow ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 size_t rtl8192_phy_QueryRFReg (struct net_device*,size_t,size_t,int /*<<< orphan*/ ) ; 

extern void PHY_RFShadowCompare(
	struct net_device		* dev,
	RF90_RADIO_PATH_E	eRFPath,
	u32					Offset)
{
	u32	reg;

	// Check if we need to check the register
	if (RF_Shadow[eRFPath][Offset].Compare == true)
	{
		reg = rtl8192_phy_QueryRFReg(dev, eRFPath, Offset, bRFRegOffsetMask);
		// Compare shadow and real rf register for 20bits!!
		if (RF_Shadow[eRFPath][Offset].Value != reg)
		{
			// Locate error position.
			RF_Shadow[eRFPath][Offset].ErrorOrNot = true;
			RT_TRACE(COMP_INIT, "PHY_RFShadowCompare RF-%d Addr%02xErr = %05x", eRFPath, Offset, reg);
		}
	}

}