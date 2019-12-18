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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IPV6_ADDR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  IPv6AddrToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MaskToStrEx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 

void Mask6AddrToStrEx(char *str, UINT size, IPV6_ADDR *mask, bool always_full_address)
{
	IP ip;

	// Validate arguments
	if (str == NULL || mask == NULL)
	{
		StrCpy(str, size, "");
		return;
	}

	IPv6AddrToIP(&ip, mask);

	MaskToStrEx(str, size, &ip, always_full_address);
}