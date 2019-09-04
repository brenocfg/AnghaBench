#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
struct TYPE_10__ {int /*<<< orphan*/  channelID; } ;
struct TYPE_9__ {TYPE_2__ header; } ;
struct TYPE_13__ {struct TYPE_13__* fragments; TYPE_4__* packet; TYPE_1__ command; } ;
struct TYPE_12__ {int /*<<< orphan*/  referenceCount; } ;
struct TYPE_11__ {int /*<<< orphan*/  dispatchedCommands; } ;
typedef  TYPE_3__ ENetPeer ;
typedef  TYPE_4__ ENetPacket ;
typedef  TYPE_5__ ENetIncomingCommand ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_5__*) ; 
 int /*<<< orphan*/  enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_remove (int /*<<< orphan*/ ) ; 

ENetPacket *
enet_peer_receive (ENetPeer * peer, enet_uint8 * channelID)
{
   ENetIncomingCommand * incomingCommand;
   ENetPacket * packet;
   
   if (enet_list_empty (& peer -> dispatchedCommands))
     return NULL;

   incomingCommand = (ENetIncomingCommand *) enet_list_remove (enet_list_begin (& peer -> dispatchedCommands));

   if (channelID != NULL)
     * channelID = incomingCommand -> command.header.channelID;

   packet = incomingCommand -> packet;

   -- packet -> referenceCount;

   if (incomingCommand -> fragments != NULL)
     enet_free (incomingCommand -> fragments);

   enet_free (incomingCommand);

   return packet;
}