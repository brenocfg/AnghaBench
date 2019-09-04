#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ state; } ;
struct TYPE_7__ {int command; int channelID; } ;
struct TYPE_8__ {TYPE_1__ header; } ;
typedef  TYPE_2__ ENetProtocol ;
typedef  TYPE_3__ ENetPeer ;

/* Variables and functions */
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int ENET_PROTOCOL_COMMAND_PING ; 
 int /*<<< orphan*/  enet_peer_queue_outgoing_command (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
enet_peer_ping (ENetPeer * peer)
{
    ENetProtocol command;

    if (peer -> state != ENET_PEER_STATE_CONNECTED)
      return;

    command.header.command = ENET_PROTOCOL_COMMAND_PING | ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE;
    command.header.channelID = 0xFF;
   
    enet_peer_queue_outgoing_command (peer, & command, NULL, 0, 0);
}