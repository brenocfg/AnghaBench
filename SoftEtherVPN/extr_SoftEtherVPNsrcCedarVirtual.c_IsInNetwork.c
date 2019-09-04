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

/* Variables and functions */
 scalar_t__ GetNetworkAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool IsInNetwork(UINT uni_addr, UINT network_addr, UINT mask)
{
	if (GetNetworkAddress(uni_addr, mask) == GetNetworkAddress(network_addr, mask))
	{
		return true;
	}
	return false;
}