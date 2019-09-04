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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  TunnelList; } ;
struct TYPE_6__ {scalar_t__ TunnelId1; int /*<<< orphan*/  ClientIp; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SERVER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

L2TP_TUNNEL *GetTunnelFromIdOfAssignedByClient(L2TP_SERVER *l2tp, IP *client_ip, UINT tunnel_id)
{
	UINT i;
	// Validate arguments
	if (l2tp == NULL || client_ip == 0 || tunnel_id == 0)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(l2tp->TunnelList);i++)
	{
		L2TP_TUNNEL *t = LIST_DATA(l2tp->TunnelList, i);

		if (t->TunnelId1 == tunnel_id && CmpIpAddr(&t->ClientIp, client_ip) == 0)
		{
			return t;
		}
	}

	return NULL;
}