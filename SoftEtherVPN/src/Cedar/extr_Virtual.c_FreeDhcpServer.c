#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * DhcpPendingLeaseList; int /*<<< orphan*/ * DhcpLeaseList; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  DHCP_LEASE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeDhcpLease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 

void FreeDhcpServer(VH *v)
{
	UINT i;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	// Empty the leases lists
	for (i = 0; i < LIST_NUM(v->DhcpLeaseList); ++i)
	{
		DHCP_LEASE *d = LIST_DATA(v->DhcpLeaseList, i);
		FreeDhcpLease(d);
	}

	ReleaseList(v->DhcpLeaseList);
	v->DhcpLeaseList = NULL;

	for (i = 0; i < LIST_NUM(v->DhcpPendingLeaseList); ++i)
	{
		DHCP_LEASE *d = LIST_DATA(v->DhcpPendingLeaseList, i);
		FreeDhcpLease(d);
	}

	ReleaseList(v->DhcpPendingLeaseList);
	v->DhcpPendingLeaseList = NULL;
}