#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint32 ;
struct TYPE_13__ {scalar_t__ state; int /*<<< orphan*/  host; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int command; int channelID; } ;
struct TYPE_12__ {TYPE_1__ disconnect; TYPE_2__ header; } ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_HOST_TO_NET_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTING ; 
 scalar_t__ ENET_PEER_STATE_ZOMBIE ; 
 int ENET_PROTOCOL_COMMAND_DISCONNECT ; 
 int ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED ; 
 int /*<<< orphan*/  enet_host_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_peer_queue_outgoing_command (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_peer_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  enet_peer_reset_queues (TYPE_4__*) ; 

void
enet_peer_disconnect_now (ENetPeer * peer, enet_uint32 data)
{
    ENetProtocol command;

    if (peer -> state == ENET_PEER_STATE_DISCONNECTED)
      return;

    if (peer -> state != ENET_PEER_STATE_ZOMBIE &&
        peer -> state != ENET_PEER_STATE_DISCONNECTING)
    {
        enet_peer_reset_queues (peer);

        command.header.command = ENET_PROTOCOL_COMMAND_DISCONNECT | ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED;
        command.header.channelID = 0xFF;
        command.disconnect.data = ENET_HOST_TO_NET_32 (data);

        enet_peer_queue_outgoing_command (peer, & command, NULL, 0, 0);

        enet_host_flush (peer -> host);
    }

    enet_peer_reset (peer);
}