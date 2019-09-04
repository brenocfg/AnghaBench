#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  ListenIP; } ;
struct TYPE_5__ {TYPE_3__* UdpListener; } ;
typedef  TYPE_1__ OPENVPN_SERVER_UDP ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddPortToUdpListener (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DeleteAllPortFromUdpListener (TYPE_3__*) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseIntList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StrToIntList (char*,int) ; 

void OvsApplyUdpPortList(OPENVPN_SERVER_UDP *u, char *port_list, IP *listen_ip)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	DeleteAllPortFromUdpListener(u->UdpListener);

	if (u->UdpListener != NULL && listen_ip != NULL)
	{
		Copy(&u->UdpListener->ListenIP, listen_ip, sizeof(IP));
	}

	o = StrToIntList(port_list, true);

	for (i = 0;i < LIST_NUM(o);i++)
	{
		UINT port = *((UINT *)LIST_DATA(o, i));

		if (port >= 1 && port <= 65535)
		{
			AddPortToUdpListener(u->UdpListener, port);
		}
	}

	ReleaseIntList(o);
}