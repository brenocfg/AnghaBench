#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  ENetPeer ;
typedef  TYPE_1__ ENetPacket ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_PACKET_FLAG_RELIABLE ; 
 int /*<<< orphan*/  enet_host_flush (int /*<<< orphan*/ ) ; 
 TYPE_1__* enet_packet_create (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_packet_resize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  enet_peer_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (char*) ; 

void send_msg(ENetPeer *peer) {
   /* Create a reliable packet of size 7 containing "packet\0" */
  ENetPacket * packet = enet_packet_create ("packet",
                                            strlen ("packet") + 1,
                                            ENET_PACKET_FLAG_RELIABLE);
  /* Extend the packet so and append the string "foo", so it now */
  /* contains "packetfoo\0" */
  enet_packet_resize (packet, strlen ("packetfoo") + 1);
  strcpy (& packet -> data [strlen ("packet")], "foo");
  /* Send the packet to the peer over channel id 0. */
  /* One could also broadcast the packet by */
  /* enet_host_broadcast (host, 0, packet); */
  enet_peer_send (peer, 0, packet);
  /* One could just use enet_host_service() instead. */
  enet_host_flush (host);
}