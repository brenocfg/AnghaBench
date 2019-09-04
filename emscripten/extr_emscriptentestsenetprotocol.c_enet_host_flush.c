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
struct TYPE_4__ {int /*<<< orphan*/  serviceTime; } ;
typedef  TYPE_1__ ENetHost ;

/* Variables and functions */
 int /*<<< orphan*/  enet_protocol_send_outgoing_commands (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_time_get () ; 

void
enet_host_flush (ENetHost * host)
{
    host -> serviceTime = enet_time_get ();

    enet_protocol_send_outgoing_commands (host, NULL, 0);
}