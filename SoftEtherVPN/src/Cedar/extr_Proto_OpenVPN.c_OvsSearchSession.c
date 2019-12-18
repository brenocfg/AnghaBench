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
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  SessionList; } ;
struct TYPE_7__ {scalar_t__ Protocol; scalar_t__ ServerPort; int /*<<< orphan*/  ServerIp; scalar_t__ ClientPort; int /*<<< orphan*/  ClientIp; } ;
typedef  TYPE_1__ OPENVPN_SESSION ;
typedef  TYPE_2__ OPENVPN_SERVER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 

OPENVPN_SESSION *OvsSearchSession(OPENVPN_SERVER *s, IP *server_ip, UINT server_port, IP *client_ip, UINT client_port, UINT protocol)
{
	OPENVPN_SESSION *se;
	OPENVPN_SESSION t;
	// Validate arguments
	if (s == NULL || server_ip == NULL || server_port == 0 || client_ip	== NULL || client_port == 0)
	{
		return NULL;
	}

	Copy(&t.ClientIp, client_ip, sizeof(IP));
	t.ClientPort = client_port;
	Copy(&t.ServerIp, server_ip, sizeof(IP));
	t.ServerPort = server_port;
	t.Protocol = protocol;

	se = Search(s->SessionList, &t);

	return se;
}