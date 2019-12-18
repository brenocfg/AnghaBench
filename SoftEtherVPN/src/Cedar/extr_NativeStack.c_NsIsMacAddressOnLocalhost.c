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
typedef  scalar_t__ UCHAR ;

/* Variables and functions */
 scalar_t__ Cmp (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ NS_MAC_ADDRESS_BYTE_1 ; 
 int /*<<< orphan*/  NsGenMacAddressSignatureForMachine (scalar_t__*,scalar_t__*) ; 

bool NsIsMacAddressOnLocalhost(UCHAR *mac)
{
	UCHAR tmp[2];
	// Validate arguments
	if (mac == NULL)
	{
		return false;
	}

	if (mac[0] != NS_MAC_ADDRESS_BYTE_1)
	{
		return false;
	}

	NsGenMacAddressSignatureForMachine(tmp, mac);

	if (Cmp(mac + 4, tmp, 2) == 0)
	{
		return true;
	}

	return false;
}