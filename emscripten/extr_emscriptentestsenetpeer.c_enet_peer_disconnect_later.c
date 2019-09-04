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
typedef  int /*<<< orphan*/  enet_uint32 ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  eventData; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  outgoingUnreliableCommands; int /*<<< orphan*/  outgoingReliableCommands; } ;
typedef  TYPE_1__ ENetPeer ;

/* Variables and functions */
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 scalar_t__ enet_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_disconnect (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
enet_peer_disconnect_later (ENetPeer * peer, enet_uint32 data)
{   
    if ((peer -> state == ENET_PEER_STATE_CONNECTED || peer -> state == ENET_PEER_STATE_DISCONNECT_LATER) && 
        ! (enet_list_empty (& peer -> outgoingReliableCommands) &&
           enet_list_empty (& peer -> outgoingUnreliableCommands) && 
           enet_list_empty (& peer -> sentReliableCommands)))
    {
        peer -> state = ENET_PEER_STATE_DISCONNECT_LATER;
        peer -> eventData = data;
    }
    else
      enet_peer_disconnect (peer, data);
}