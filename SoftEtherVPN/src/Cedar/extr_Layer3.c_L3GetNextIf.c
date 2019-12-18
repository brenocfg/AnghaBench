#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_11__ {int IpAddress; int SubnetMask; } ;
struct TYPE_10__ {int /*<<< orphan*/  IfList; } ;
struct TYPE_9__ {int GatewayAddress; } ;
typedef  TYPE_1__ L3TABLE ;
typedef  TYPE_2__ L3SW ;
typedef  TYPE_3__ L3IF ;

/* Variables and functions */
 TYPE_1__* L3GetBestRoute (TYPE_2__*,int) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 

L3IF *L3GetNextIf(L3SW *s, UINT ip, UINT *next_hop)
{
	UINT i;
	L3IF *f;
	UINT next_hop_ip = 0;
	// Validate arguments
	if (s == NULL || ip == 0 || ip == 0xffffffff)
	{
		return NULL;
	}

	f = NULL;

	// Examine whether the specified IP address is contained
	// in the networks which each interfaces belong to
	for (i = 0;i < LIST_NUM(s->IfList);i++)
	{
		L3IF *ff = LIST_DATA(s->IfList, i);

		if ((ff->IpAddress & ff->SubnetMask) == (ip & ff->SubnetMask))
		{
			f = ff;
			next_hop_ip = ip;
			break;
		}
	}

	if (f == NULL)
	{
		// Find the routing table if it's not found
		L3TABLE *t = L3GetBestRoute(s, ip);

		if (t == NULL)
		{
			// Still not found
			return NULL;
		}
		else
		{
			// Find the interface with the IP address of the router of
			// NextHop of the found route
			for (i = 0;i < LIST_NUM(s->IfList);i++)
			{
				L3IF *ff = LIST_DATA(s->IfList, i);

				if ((ff->IpAddress & ff->SubnetMask) == (t->GatewayAddress & ff->SubnetMask))
				{
					f = ff;
					next_hop_ip = t->GatewayAddress;
					break;
				}
			}
		}
	}

	if (f == NULL)
	{
		// Destination interface was unknown after all
		return NULL;
	}

	if (next_hop != NULL)
	{
		*next_hop = next_hop_ip;
	}

	return f;
}