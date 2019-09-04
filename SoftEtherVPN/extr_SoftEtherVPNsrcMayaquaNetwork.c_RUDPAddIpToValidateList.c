#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ ExpiresTick; int /*<<< orphan*/  ClientIP; } ;
struct TYPE_8__ {int /*<<< orphan*/ * NatT_SourceIpList; } ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  TYPE_2__ RUDP_SOURCE_IP ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 scalar_t__ RUDP_MAX_VALIDATED_SOURCE_IP_ADDRESSES ; 
 scalar_t__ RUDP_VALIDATED_SOURCE_IP_ADDRESS_EXPIRES ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 TYPE_2__* ZeroMalloc (int) ; 

void RUDPAddIpToValidateList(RUDP_STACK *r, IP *ip)
{
	UINT i;
	RUDP_SOURCE_IP *sip;
	UINT64 now = Tick64();
	LIST *o = NULL;
	// Validate arguments
	if (r == NULL || ip == NULL)
	{
		return;
	}

	if (LIST_NUM(r->NatT_SourceIpList) >= RUDP_MAX_VALIDATED_SOURCE_IP_ADDRESSES)
	{
		return;
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

	sip = NULL;

	for (i = 0;i < LIST_NUM(r->NatT_SourceIpList);i++)
	{
		RUDP_SOURCE_IP *s = (RUDP_SOURCE_IP *)LIST_DATA(r->NatT_SourceIpList, i);

		if (CmpIpAddr(&s->ClientIP, ip) == 0)
		{
			sip = s;
			break;
		}
	}

	if (sip == NULL)
	{
		sip = ZeroMalloc(sizeof(RUDP_SOURCE_IP));

		Copy(&sip->ClientIP, ip, sizeof(IP));

		Add(r->NatT_SourceIpList, sip);
	}

	sip->ExpiresTick = now + (UINT64)RUDP_VALIDATED_SOURCE_IP_ADDRESS_EXPIRES;

	Debug("RUDP: NAT-T: Src IP added: %r (current list len = %u)\n", ip, LIST_NUM(r->NatT_SourceIpList));
}