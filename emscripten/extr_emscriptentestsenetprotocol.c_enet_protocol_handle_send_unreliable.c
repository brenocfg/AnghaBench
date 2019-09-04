#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
struct TYPE_15__ {size_t receivedDataLength; int /*<<< orphan*/ * receivedData; } ;
struct TYPE_14__ {scalar_t__ channelCount; scalar_t__ state; } ;
struct TYPE_12__ {int /*<<< orphan*/  dataLength; } ;
struct TYPE_11__ {scalar_t__ channelID; } ;
struct TYPE_13__ {TYPE_2__ sendUnreliable; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  ENetProtocolSendUnreliable ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;
typedef  int /*<<< orphan*/  ENetPacket ;
typedef  TYPE_5__ ENetHost ;

/* Variables and functions */
 size_t ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 size_t ENET_PROTOCOL_MAXIMUM_PACKET_SIZE ; 
 int /*<<< orphan*/ * enet_packet_create (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * enet_peer_queue_incoming_command (TYPE_4__*,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enet_protocol_handle_send_unreliable (ENetHost * host, ENetPeer * peer, const ENetProtocol * command, enet_uint8 ** currentData)
{
    ENetPacket * packet;
    size_t dataLength;

    if (command -> header.channelID >= peer -> channelCount ||
        (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER))
      return -1;

    dataLength = ENET_NET_TO_HOST_16 (command -> sendUnreliable.dataLength);
    * currentData += dataLength;
    if (dataLength > ENET_PROTOCOL_MAXIMUM_PACKET_SIZE ||
        * currentData < host -> receivedData ||
        * currentData > & host -> receivedData [host -> receivedDataLength])
      return -1;

    packet = enet_packet_create ((const enet_uint8 *) command + sizeof (ENetProtocolSendUnreliable),
                                 dataLength,
                                 0);
    if (packet == NULL ||
        enet_peer_queue_incoming_command (peer, command, packet, 0) == NULL)
      return -1;

    return 0;
}