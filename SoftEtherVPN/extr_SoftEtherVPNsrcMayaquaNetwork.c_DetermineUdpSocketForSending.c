#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {scalar_t__ SrcPort; int /*<<< orphan*/  DstIP; int /*<<< orphan*/  SrcIP; } ;
typedef  TYPE_1__ UDPPACKET ;
struct TYPE_9__ {int HasError; scalar_t__ Port; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/ * Sock; } ;
typedef  TYPE_2__ UDPLISTENER_SOCK ;
struct TYPE_10__ {int /*<<< orphan*/  SockList; } ;
typedef  TYPE_3__ UDPLISTENER ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZeroIP (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

UDPLISTENER_SOCK *DetermineUdpSocketForSending(UDPLISTENER *u, UDPPACKET *p)
{
	UINT i;
	// Validate arguments
	if (u == NULL || p == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(u->SockList);i++)
	{
		UDPLISTENER_SOCK *us = LIST_DATA(u->SockList, i);

		if (us->Sock != NULL && us->HasError == false)
		{
			if (us->Port == p->SrcPort)
			{
				if (CmpIpAddr(&us->IpAddress, &p->SrcIP) == 0)
				{
					return us;
				}
			}
		}
	}

	for (i = 0;i < LIST_NUM(u->SockList);i++)
	{
		UDPLISTENER_SOCK *us = LIST_DATA(u->SockList, i);

		if (us->Sock != NULL && us->HasError == false)
		{
			if (us->Port == p->SrcPort)
			{
				if (IsZeroIP(&us->IpAddress))
				{
					if ((IsIP4(&p->DstIP) && IsIP4(&us->IpAddress)) ||
						(IsIP6(&p->DstIP) && IsIP6(&us->IpAddress)))
					{
						return us;
					}
				}
			}
		}
	}

	return NULL;
}