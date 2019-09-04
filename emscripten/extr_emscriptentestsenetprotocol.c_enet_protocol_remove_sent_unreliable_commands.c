#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ referenceCount; } ;
struct TYPE_7__ {TYPE_4__* packet; int /*<<< orphan*/  outgoingCommandList; } ;
struct TYPE_6__ {int /*<<< orphan*/  sentUnreliableCommands; } ;
typedef  TYPE_1__ ENetPeer ;
typedef  TYPE_2__ ENetOutgoingCommand ;

/* Variables and functions */
 int /*<<< orphan*/  enet_free (TYPE_2__*) ; 
 int /*<<< orphan*/  enet_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_front (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_4__*) ; 

__attribute__((used)) static void
enet_protocol_remove_sent_unreliable_commands (ENetPeer * peer)
{
    ENetOutgoingCommand * outgoingCommand;

    while (! enet_list_empty (& peer -> sentUnreliableCommands))
    {
        outgoingCommand = (ENetOutgoingCommand *) enet_list_front (& peer -> sentUnreliableCommands);
        
        enet_list_remove (& outgoingCommand -> outgoingCommandList);

        if (outgoingCommand -> packet != NULL)
        {
           -- outgoingCommand -> packet -> referenceCount;

           if (outgoingCommand -> packet -> referenceCount == 0)
             enet_packet_destroy (outgoingCommand -> packet);
        }

        enet_free (outgoingCommand);
    }
}