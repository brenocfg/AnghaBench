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
struct TYPE_4__ {int /*<<< orphan*/ * packet; int /*<<< orphan*/ * peer; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  ENetHost ;
typedef  TYPE_1__ ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_EVENT_TYPE_NONE ; 
 int enet_protocol_dispatch_incoming_commands (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
enet_host_check_events (ENetHost * host, ENetEvent * event)
{
    if (event == NULL) return -1;

    event -> type = ENET_EVENT_TYPE_NONE;
    event -> peer = NULL;
    event -> packet = NULL;

    return enet_protocol_dispatch_incoming_commands (host, event);
}