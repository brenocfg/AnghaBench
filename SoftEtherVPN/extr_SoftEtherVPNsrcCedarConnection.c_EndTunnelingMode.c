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
struct TYPE_5__ {scalar_t__ Protocol; } ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 scalar_t__ CONNECTION_TCP ; 
 int /*<<< orphan*/  DisconnectTcpSockets (TYPE_1__*) ; 
 int /*<<< orphan*/  DisconnectUDPSockets (TYPE_1__*) ; 

void EndTunnelingMode(CONNECTION *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	// Protocol
	if (c->Protocol == CONNECTION_TCP)
	{
		// TCP
		DisconnectTcpSockets(c);
	}
	else
	{
		// UDP
		DisconnectUDPSockets(c);
	}
}