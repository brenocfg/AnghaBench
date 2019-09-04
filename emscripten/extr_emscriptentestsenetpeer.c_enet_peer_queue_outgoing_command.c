#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint32 ;
typedef  int /*<<< orphan*/  enet_uint16 ;
struct TYPE_7__ {TYPE_1__* packet; int /*<<< orphan*/  fragmentLength; int /*<<< orphan*/  fragmentOffset; int /*<<< orphan*/  command; } ;
struct TYPE_6__ {int /*<<< orphan*/  referenceCount; } ;
typedef  int /*<<< orphan*/  ENetProtocol ;
typedef  int /*<<< orphan*/  ENetPeer ;
typedef  TYPE_1__ ENetPacket ;
typedef  TYPE_2__ ENetOutgoingCommand ;

/* Variables and functions */
 scalar_t__ enet_malloc (int) ; 
 int /*<<< orphan*/  enet_peer_setup_outgoing_command (int /*<<< orphan*/ *,TYPE_2__*) ; 

ENetOutgoingCommand *
enet_peer_queue_outgoing_command (ENetPeer * peer, const ENetProtocol * command, ENetPacket * packet, enet_uint32 offset, enet_uint16 length)
{
    ENetOutgoingCommand * outgoingCommand = (ENetOutgoingCommand *) enet_malloc (sizeof (ENetOutgoingCommand));
    if (outgoingCommand == NULL)
      return NULL;

    outgoingCommand -> command = * command;
    outgoingCommand -> fragmentOffset = offset;
    outgoingCommand -> fragmentLength = length;
    outgoingCommand -> packet = packet;
    if (packet != NULL)
      ++ packet -> referenceCount;

    enet_peer_setup_outgoing_command (peer, outgoingCommand);

    return outgoingCommand;
}