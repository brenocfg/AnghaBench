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
typedef  int /*<<< orphan*/  enet_uint8 ;
struct TYPE_11__ {size_t peerCount; TYPE_1__* peers; } ;
struct TYPE_10__ {scalar_t__ referenceCount; } ;
struct TYPE_9__ {scalar_t__ state; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetPacket ;
typedef  TYPE_3__ ENetHost ;

/* Variables and functions */
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  enet_peer_send (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

void
enet_host_broadcast (ENetHost * host, enet_uint8 channelID, ENetPacket * packet)
{
    ENetPeer * currentPeer;

    for (currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
       if (currentPeer -> state != ENET_PEER_STATE_CONNECTED)
         continue;

       enet_peer_send (currentPeer, channelID, packet);
    }

    if (packet -> referenceCount == 0)
      enet_packet_destroy (packet);
}