#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Cedar; int /*<<< orphan*/  OpenVpnServer; int /*<<< orphan*/  UdpListener; } ;
typedef  TYPE_1__ OPENVPN_SERVER_UDP ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeOpenVpnServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpListener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 

void FreeOpenVpnServerUdp(OPENVPN_SERVER_UDP *u)
{
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	// Stop the UDP listener
	FreeUdpListener(u->UdpListener);

	// Release the OpenVPN server
	FreeOpenVpnServer(u->OpenVpnServer);

	ReleaseCedar(u->Cedar);

	Free(u);
}