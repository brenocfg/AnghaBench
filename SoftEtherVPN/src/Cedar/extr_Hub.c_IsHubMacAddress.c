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
typedef  int UCHAR ;

/* Variables and functions */
 int SE_HUB_MAC_ADDR_SIGN ; 

bool IsHubMacAddress(UCHAR *mac)
{
	// Validate arguments
	if (mac == NULL)
	{
		return false;
	}

	if (mac[0] == 0x00 && mac[1] == SE_HUB_MAC_ADDR_SIGN)
	{
		return true;
	}

	return false;
}