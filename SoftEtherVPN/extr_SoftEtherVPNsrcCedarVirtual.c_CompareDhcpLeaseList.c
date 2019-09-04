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
struct TYPE_2__ {int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_1__ DHCP_LEASE ;

/* Variables and functions */
 int Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int CompareDhcpLeaseList(void *p1, void *p2)
{
	DHCP_LEASE *d1, *d2;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	d1 = *(DHCP_LEASE **)p1;
	d2 = *(DHCP_LEASE **)p2;
	if (d1 == NULL || d2 == NULL)
	{
		return 0;
	}

	return Cmp(d1->MacAddress, d2->MacAddress, 6);
}