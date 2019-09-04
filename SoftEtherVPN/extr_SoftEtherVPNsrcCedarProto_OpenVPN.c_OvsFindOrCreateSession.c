#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  SessionList; } ;
typedef  int /*<<< orphan*/  OPENVPN_SESSION ;
typedef  TYPE_1__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OvsNewSession (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * OvsSearchSession (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

OPENVPN_SESSION *OvsFindOrCreateSession(OPENVPN_SERVER *s, IP *server_ip, UINT server_port, IP *client_ip, UINT client_port, UINT protocol)
{
	OPENVPN_SESSION *se;
	// Validate arguments
	if (s == NULL || server_ip == NULL || server_port == 0 || client_ip	== NULL || client_port == 0)
	{
		return NULL;
	}

	se = OvsSearchSession(s, server_ip, server_port, client_ip, client_port, protocol);
	if (se == NULL)
	{
		se = OvsNewSession(s, server_ip, server_port, client_ip, client_port, protocol);

		if (se != NULL)
		{
			Insert(s->SessionList, se);
		}
	}

	return se;
}