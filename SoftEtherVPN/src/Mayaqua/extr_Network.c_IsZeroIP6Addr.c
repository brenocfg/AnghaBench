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
typedef  int /*<<< orphan*/  IPV6_ADDR ;

/* Variables and functions */
 int IsZero (int /*<<< orphan*/ *,int) ; 

bool IsZeroIP6Addr(IPV6_ADDR *addr)
{
	// Validate arguments
	if (addr == NULL)
	{
		return true;
	}

	return IsZero(addr, sizeof(IPV6_ADDR));
}