#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int recalculateBandwidthLimits; } ;
struct TYPE_16__ {scalar_t__ state; int /*<<< orphan*/  eventData; } ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int command; } ;
struct TYPE_15__ {TYPE_2__ disconnect; TYPE_1__ header; } ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;
typedef  TYPE_5__ ENetHost ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_NET_TO_HOST_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT ; 
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_CONNECTION_PENDING ; 
 scalar_t__ ENET_PEER_STATE_CONNECTION_SUCCEEDED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTING ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 scalar_t__ ENET_PEER_STATE_ZOMBIE ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int /*<<< orphan*/  enet_peer_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  enet_peer_reset_queues (TYPE_4__*) ; 
 int /*<<< orphan*/  enet_protocol_dispatch_state (TYPE_5__*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int
enet_protocol_handle_disconnect (ENetHost * host, ENetPeer * peer, const ENetProtocol * command)
{
    if (peer -> state == ENET_PEER_STATE_ZOMBIE || peer -> state == ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT)
      return 0;

    enet_peer_reset_queues (peer);

    if (peer -> state == ENET_PEER_STATE_CONNECTION_SUCCEEDED || peer -> state == ENET_PEER_STATE_DISCONNECTING)
        enet_protocol_dispatch_state (host, peer, ENET_PEER_STATE_ZOMBIE);
    else
    if (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER)
    {
        if (peer -> state == ENET_PEER_STATE_CONNECTION_PENDING) host -> recalculateBandwidthLimits = 1;

        enet_peer_reset (peer);
    }
    else
    if (command -> header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE)
      peer -> state = ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT;
    else
      enet_protocol_dispatch_state (host, peer, ENET_PEER_STATE_ZOMBIE);

    if (peer -> state != ENET_PEER_STATE_DISCONNECTED)
      peer -> eventData = ENET_NET_TO_HOST_32 (command -> disconnect.data);

    return 0;
}