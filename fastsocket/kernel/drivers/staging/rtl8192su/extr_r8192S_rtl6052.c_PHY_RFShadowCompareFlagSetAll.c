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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PHY_RFShadowCompareFlagSet (struct net_device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RF6052_MAX_PATH ; 
 scalar_t__ RF6052_MAX_REG ; 
 int /*<<< orphan*/  TRUE ; 

extern void PHY_RFShadowCompareFlagSetAll(struct net_device  * dev)
{
	u32		eRFPath;
	u32		Offset;

	for (eRFPath = 0; eRFPath < RF6052_MAX_PATH; eRFPath++)
	{
		for (Offset = 0; Offset <= RF6052_MAX_REG; Offset++)
		{
			// 2008/11/20 MH For S3S4 test, we only check reg 26/27 now!!!!
			if (Offset != 0x26 && Offset != 0x27)
				PHY_RFShadowCompareFlagSet(dev, (RF90_RADIO_PATH_E)eRFPath, Offset, FALSE);
			else
				PHY_RFShadowCompareFlagSet(dev, (RF90_RADIO_PATH_E)eRFPath, Offset, TRUE);
		}
	}

}