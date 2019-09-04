#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ data; TYPE_1__* peer; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int recalculateBandwidthLimits; } ;
struct TYPE_10__ {scalar_t__ state; scalar_t__ eventData; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetHost ;
typedef  TYPE_3__ ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_EVENT_TYPE_DISCONNECT ; 
 scalar_t__ ENET_PEER_STATE_CONNECTING ; 
 scalar_t__ ENET_PEER_STATE_CONNECTION_PENDING ; 
 scalar_t__ ENET_PEER_STATE_CONNECTION_SUCCEEDED ; 
 int /*<<< orphan*/  ENET_PEER_STATE_ZOMBIE ; 
 int /*<<< orphan*/  enet_peer_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  enet_protocol_dispatch_state (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enet_protocol_notify_disconnect (ENetHost * host, ENetPeer * peer, ENetEvent * event)
{
    if (peer -> state >= ENET_PEER_STATE_CONNECTION_PENDING)
       host -> recalculateBandwidthLimits = 1;

    if (peer -> state != ENET_PEER_STATE_CONNECTING && peer -> state < ENET_PEER_STATE_CONNECTION_SUCCEEDED)
        enet_peer_reset (peer);
    else
    if (event != NULL)
    {
        event -> type = ENET_EVENT_TYPE_DISCONNECT;
        event -> peer = peer;
        event -> data = 0;

        enet_peer_reset (peer);
    }
    else 
    {
        peer -> eventData = 0;

        enet_protocol_dispatch_state (host, peer, ENET_PEER_STATE_ZOMBIE);
    }
}