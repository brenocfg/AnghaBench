#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; TYPE_1__* peer; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int recalculateBandwidthLimits; } ;
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  eventData; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetHost ;
typedef  TYPE_3__ ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_EVENT_TYPE_CONNECT ; 
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_CONNECTING ; 
 int /*<<< orphan*/  ENET_PEER_STATE_CONNECTION_PENDING ; 
 int /*<<< orphan*/  ENET_PEER_STATE_CONNECTION_SUCCEEDED ; 
 int /*<<< orphan*/  enet_protocol_dispatch_state (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enet_protocol_notify_connect (ENetHost * host, ENetPeer * peer, ENetEvent * event)
{
    host -> recalculateBandwidthLimits = 1;

    if (event != NULL)
    {
        peer -> state = ENET_PEER_STATE_CONNECTED;

        event -> type = ENET_EVENT_TYPE_CONNECT;
        event -> peer = peer;
        event -> data = peer -> eventData;
    }
    else 
        enet_protocol_dispatch_state (host, peer, peer -> state == ENET_PEER_STATE_CONNECTING ? ENET_PEER_STATE_CONNECTION_SUCCEEDED : ENET_PEER_STATE_CONNECTION_PENDING);
}