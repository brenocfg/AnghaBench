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
struct TYPE_6__ {int /*<<< orphan*/  NatTable; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int DisconnectNow; scalar_t__ SrcIp; scalar_t__ Protocol; scalar_t__ TcpStatus; scalar_t__ LastCommTime; } ;
typedef  TYPE_2__ NAT_ENTRY ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ NAT_TCP ; 
 scalar_t__ NAT_TCP_CONNECTING ; 

NAT_ENTRY *GetOldestNatEntryOfIp(VH *v, UINT ip, UINT protocol)
{
	UINT i;
	NAT_ENTRY *oldest = NULL;
	UINT64 oldest_tick = 0xFFFFFFFFFFFFFFFFULL;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(v->NatTable);i++)
	{
		NAT_ENTRY *e = LIST_DATA(v->NatTable, i);

		if (e->DisconnectNow == false)
		{
			if (e->SrcIp == ip)
			{
				if (e->Protocol == protocol)
				{
					if (protocol != NAT_TCP || e->TcpStatus != NAT_TCP_CONNECTING)
					{
						if (e->LastCommTime <= oldest_tick)
						{
							oldest_tick = e->LastCommTime;
							oldest = e;
						}
					}
				}
			}
		}
	}

	return oldest;
}