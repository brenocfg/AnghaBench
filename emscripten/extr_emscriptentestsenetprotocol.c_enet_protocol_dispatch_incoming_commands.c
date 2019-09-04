#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* peer; int /*<<< orphan*/  type; int /*<<< orphan*/ * packet; int /*<<< orphan*/  channelID; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int recalculateBandwidthLimits; int /*<<< orphan*/  dispatchQueue; } ;
struct TYPE_8__ {int needsDispatch; int state; int /*<<< orphan*/  dispatchList; int /*<<< orphan*/  dispatchedCommands; int /*<<< orphan*/  eventData; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetHost ;
typedef  TYPE_3__ ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_EVENT_TYPE_CONNECT ; 
 int /*<<< orphan*/  ENET_EVENT_TYPE_DISCONNECT ; 
 int /*<<< orphan*/  ENET_EVENT_TYPE_RECEIVE ; 
#define  ENET_PEER_STATE_CONNECTED 131 
#define  ENET_PEER_STATE_CONNECTION_PENDING 130 
#define  ENET_PEER_STATE_CONNECTION_SUCCEEDED 129 
#define  ENET_PEER_STATE_ZOMBIE 128 
 int /*<<< orphan*/  enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * enet_peer_receive (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_reset (TYPE_1__*) ; 

__attribute__((used)) static int
enet_protocol_dispatch_incoming_commands (ENetHost * host, ENetEvent * event)
{
    while (! enet_list_empty (& host -> dispatchQueue))
    {
       ENetPeer * peer = (ENetPeer *) enet_list_remove (enet_list_begin (& host -> dispatchQueue));

       peer -> needsDispatch = 0;

       switch (peer -> state)
       {
       case ENET_PEER_STATE_CONNECTION_PENDING:
       case ENET_PEER_STATE_CONNECTION_SUCCEEDED:
           peer -> state = ENET_PEER_STATE_CONNECTED;

           event -> type = ENET_EVENT_TYPE_CONNECT;
           event -> peer = peer;
           event -> data = peer -> eventData;

           return 1;
           
       case ENET_PEER_STATE_ZOMBIE:
           host -> recalculateBandwidthLimits = 1;

           event -> type = ENET_EVENT_TYPE_DISCONNECT;
           event -> peer = peer;
           event -> data = peer -> eventData;

           enet_peer_reset (peer);

           return 1;

       case ENET_PEER_STATE_CONNECTED:
           if (enet_list_empty (& peer -> dispatchedCommands))
             continue;

           event -> packet = enet_peer_receive (peer, & event -> channelID);
           if (event -> packet == NULL)
             continue;
             
           event -> type = ENET_EVENT_TYPE_RECEIVE;
           event -> peer = peer;

           if (! enet_list_empty (& peer -> dispatchedCommands))
           {
              peer -> needsDispatch = 1;
         
              enet_list_insert (enet_list_end (& host -> dispatchQueue), & peer -> dispatchList);
           }

           return 1;
       }
    }

    return 0;
}