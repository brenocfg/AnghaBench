#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  NatTable; int /*<<< orphan*/  NativeNat; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {int Protocol; } ;
typedef  TYPE_2__ NAT_ENTRY ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
#define  NAT_DNS 131 
#define  NAT_ICMP 130 
#define  NAT_TCP 129 
#define  NAT_UDP 128 
 scalar_t__ NnIsActive (TYPE_1__*) ; 
 int /*<<< orphan*/  NnPoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PollingNatDns (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PollingNatIcmp (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PollingNatTcp (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  PoolingNatUdp (TYPE_1__*,TYPE_2__*) ; 

void PoolingNat(VH *v)
{
	UINT i;
	// Validate arguments
	if (v == NULL)
	{
		return;
	}

	if (NnIsActive(v))
	{
		// Poll whether the packet comes from native NAT
		NnPoll(v->NativeNat);
	}

	// Process by scanning the all NAT entries
	for (i = 0;i < LIST_NUM(v->NatTable);i++)
	{
		NAT_ENTRY *n = LIST_DATA(v->NatTable, i);

		switch (n->Protocol)
		{
		case NAT_TCP:
			PollingNatTcp(v, n);
			break;

		case NAT_UDP:
			PoolingNatUdp(v, n);
			break;

		case NAT_ICMP:
			PollingNatIcmp(v, n);
			break;

		case NAT_DNS:
			PollingNatDns(v, n);
			break;
		}
	}
}