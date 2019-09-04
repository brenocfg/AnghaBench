#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ incomingReliableSequenceNumber; int /*<<< orphan*/  incomingUnreliableCommands; int /*<<< orphan*/  incomingUnreliableSequenceNumber; } ;
struct TYPE_9__ {int command; } ;
struct TYPE_10__ {TYPE_1__ header; } ;
struct TYPE_13__ {scalar_t__ reliableSequenceNumber; scalar_t__ fragmentsRemaining; int /*<<< orphan*/  unreliableSequenceNumber; TYPE_2__ command; } ;
struct TYPE_12__ {int needsDispatch; int /*<<< orphan*/  dispatchList; TYPE_3__* host; int /*<<< orphan*/  dispatchedCommands; } ;
struct TYPE_11__ {int /*<<< orphan*/  dispatchQueue; } ;
typedef  TYPE_4__ ENetPeer ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_5__ ENetIncomingCommand ;
typedef  TYPE_6__ ENetChannel ;

/* Variables and functions */
 int ENET_PROTOCOL_COMMAND_MASK ; 
 int ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED ; 
 scalar_t__ enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_move (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 
 int /*<<< orphan*/  enet_list_previous (scalar_t__) ; 
 int /*<<< orphan*/  enet_peer_remove_incoming_commands (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void
enet_peer_dispatch_incoming_unreliable_commands (ENetPeer * peer, ENetChannel * channel)
{
    ENetListIterator droppedCommand, startCommand, currentCommand;

    for (droppedCommand = startCommand = currentCommand = enet_list_begin (& channel -> incomingUnreliableCommands);
         currentCommand != enet_list_end (& channel -> incomingUnreliableCommands);
         currentCommand = enet_list_next (currentCommand))
    {
       ENetIncomingCommand * incomingCommand = (ENetIncomingCommand *) currentCommand;

       if ((incomingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK) == ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED)
         continue;
       else
       if (incomingCommand -> reliableSequenceNumber != channel -> incomingReliableSequenceNumber)
         break;
       else
       if (incomingCommand -> fragmentsRemaining <= 0)
         channel -> incomingUnreliableSequenceNumber = incomingCommand -> unreliableSequenceNumber;
       else
       if (startCommand == currentCommand)
         startCommand = enet_list_next (currentCommand);
       else
       {
            enet_list_move (enet_list_end (& peer -> dispatchedCommands), startCommand, enet_list_previous (currentCommand));

            if (! peer -> needsDispatch)
            {
                enet_list_insert (enet_list_end (& peer -> host -> dispatchQueue), & peer -> dispatchList);

                peer -> needsDispatch = 1;
            }

            droppedCommand = startCommand = enet_list_next (currentCommand); 
       }
    }

    if (startCommand != currentCommand)
    {
        enet_list_move (enet_list_end (& peer -> dispatchedCommands), startCommand, enet_list_previous (currentCommand));

        if (! peer -> needsDispatch)
        {
            enet_list_insert (enet_list_end (& peer -> host -> dispatchQueue), & peer -> dispatchList);

            peer -> needsDispatch = 1;
        }

        droppedCommand = startCommand = enet_list_next (currentCommand);
    }

    enet_peer_remove_incoming_commands (& channel -> incomingUnreliableCommands, enet_list_begin (& channel -> incomingUnreliableCommands), droppedCommand);
}