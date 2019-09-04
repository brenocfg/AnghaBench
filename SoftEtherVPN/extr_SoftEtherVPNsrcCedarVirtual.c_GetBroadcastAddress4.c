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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  GetBroadcastAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void GetBroadcastAddress4(IP *dst, IP *addr, IP *mask)
{
	// Validate arguments
	if (dst == NULL || IsIP4(addr) == false || IsIP4(mask) == false)
	{
		Zero(dst, sizeof(IP));
		return;
	}

	UINTToIP(dst, GetBroadcastAddress(IPToUINT(addr), IPToUINT(mask)));
}