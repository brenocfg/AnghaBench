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

/* Variables and functions */
 int IsBridgeSupported () ; 
 scalar_t__ IsEthSupported () ; 

bool IsNeedWinPcap()
{
	if (IsBridgeSupported() == false)
	{
		// Not in Windows
		return false;
	}
	else
	{
		// Windows
		if (IsEthSupported())
		{
			// Already success to access the Ethernet device
			return false;
		}
		else
		{
			// Failed to access the Ethernet device
			return true;
		}
	}
}