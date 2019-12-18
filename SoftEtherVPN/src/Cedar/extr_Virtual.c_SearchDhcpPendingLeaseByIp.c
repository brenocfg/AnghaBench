#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  DhcpPendingLeaseList; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ IpAddress; } ;
typedef  TYPE_2__ DHCP_LEASE ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

DHCP_LEASE *SearchDhcpPendingLeaseByIp(VH *v, UINT ip)
{
	UINT i;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	for (i = 0; i < LIST_NUM(v->DhcpPendingLeaseList); ++i)
	{
		DHCP_LEASE *d = LIST_DATA(v->DhcpPendingLeaseList, i);
		if (d->IpAddress == ip)
		{
			return d;
		}
	}

	return NULL;
}