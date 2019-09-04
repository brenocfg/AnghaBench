#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ ClientPort; scalar_t__ ServerPort; int /*<<< orphan*/  ServerIP; int /*<<< orphan*/  ClientIP; } ;
struct TYPE_8__ {scalar_t__ InitiatorCookie; scalar_t__ Mode; TYPE_3__* IkeClient; } ;
struct TYPE_7__ {int /*<<< orphan*/  IkeSaList; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  TYPE_2__ IKE_SA ;
typedef  TYPE_3__ IKE_CLIENT ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

IKE_SA *FindIkeSaByEndPointAndInitiatorCookie(IKE_SERVER *ike, IP *client_ip, UINT client_port, IP *server_ip, UINT server_port, UINT64 init_cookie, UINT mode)
{
	UINT i;
	// Validate arguments
	if (ike == NULL || client_ip == NULL || server_ip == NULL || client_port == 0 || server_port == 0 || init_cookie == 0)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);
		IKE_CLIENT *c;

		c = sa->IkeClient;

		if (CmpIpAddr(&c->ClientIP, client_ip) == 0 &&
			CmpIpAddr(&c->ServerIP, server_ip) == 0 &&
			c->ClientPort == client_port &&
			c->ServerPort == server_port &&
			sa->InitiatorCookie == init_cookie &&
			sa->Mode == mode)
		{
			return sa;
		}
	}

	return NULL;
}