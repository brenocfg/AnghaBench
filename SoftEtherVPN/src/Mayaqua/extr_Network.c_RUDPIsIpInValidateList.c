#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ ExpiresTick; int /*<<< orphan*/  ClientIP; } ;
struct TYPE_7__ {int /*<<< orphan*/ * NatT_SourceIpList; } ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_2__ RUDP_SOURCE_IP ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 scalar_t__ IsIPAddressInSameLocalNetwork (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIPPrivate (int /*<<< orphan*/ *) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 

bool RUDPIsIpInValidateList(RUDP_STACK *r, IP *ip)
{
	UINT i;
	UINT64 now = Tick64();
	LIST *o = NULL;
	bool ret = false;
	// Validate arguments
	if (r == NULL || ip == NULL)
	{
		return false;
	}

	// Always allow private IP addresses
	if (IsIPPrivate(ip))
	{
		return true;
	}

	if (IsIPAddressInSameLocalNetwork(ip))
	{
		return true;
	}

	for (i = 0;i < LIST_NUM(r->NatT_SourceIpList);i++)
	{
		RUDP_SOURCE_IP *s = (RUDP_SOURCE_IP *)LIST_DATA(r->NatT_SourceIpList, i);

		if (s->ExpiresTick <= now)
		{
			if (o == NULL)
			{
				o = NewListFast(NULL);
			}

			Add(o, s);
		}
	}

	if (o != NULL)
	{
		for (i = 0;i < LIST_NUM(o);i++)
		{
			RUDP_SOURCE_IP *s = (RUDP_SOURCE_IP *)LIST_DATA(o, i);

			Delete(r->NatT_SourceIpList, s);

			Free(s);
		}

		ReleaseList(o);
	}

	for (i = 0;i < LIST_NUM(r->NatT_SourceIpList);i++)
	{
		RUDP_SOURCE_IP *s = (RUDP_SOURCE_IP *)LIST_DATA(r->NatT_SourceIpList, i);

		if (CmpIpAddr(&s->ClientIP, ip) == 0)
		{
			ret = true;
			break;
		}
	}

	Debug("RUDP: NAT-T: Validate IP: %r, ret=%u (current list len = %u)\n", ip, ret, LIST_NUM(r->NatT_SourceIpList));

	return ret;
}