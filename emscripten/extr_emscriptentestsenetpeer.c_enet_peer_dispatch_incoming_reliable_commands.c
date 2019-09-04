#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ enet_uint16 ;
struct TYPE_12__ {scalar_t__ incomingReliableSequenceNumber; int /*<<< orphan*/  incomingReliableCommands; scalar_t__ incomingUnreliableSequenceNumber; } ;
struct TYPE_11__ {scalar_t__ fragmentsRemaining; scalar_t__ reliableSequenceNumber; int fragmentCount; } ;
struct TYPE_10__ {int needsDispatch; int /*<<< orphan*/  dispatchList; TYPE_1__* host; int /*<<< orphan*/  dispatchedCommands; } ;
struct TYPE_9__ {int /*<<< orphan*/  dispatchQueue; } ;
typedef  TYPE_2__ ENetPeer ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_3__ ENetIncomingCommand ;
typedef  TYPE_4__ ENetChannel ;

/* Variables and functions */
 scalar_t__ enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_move (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 
 int /*<<< orphan*/  enet_list_previous (scalar_t__) ; 
 int /*<<< orphan*/  enet_peer_dispatch_incoming_unreliable_commands (TYPE_2__*,TYPE_4__*) ; 

void
enet_peer_dispatch_incoming_reliable_commands (ENetPeer * peer, ENetChannel * channel)
{
    ENetListIterator currentCommand;

    for (currentCommand = enet_list_begin (& channel -> incomingReliableCommands);
         currentCommand != enet_list_end (& channel -> incomingReliableCommands);
         currentCommand = enet_list_next (currentCommand))
    {
       ENetIncomingCommand * incomingCommand = (ENetIncomingCommand *) currentCommand;
         
       if (incomingCommand -> fragmentsRemaining > 0 ||
           incomingCommand -> reliableSequenceNumber != (enet_uint16) (channel -> incomingReliableSequenceNumber + 1))
         break;

       channel -> incomingReliableSequenceNumber = incomingCommand -> reliableSequenceNumber;

       if (incomingCommand -> fragmentCount > 0)
         channel -> incomingReliableSequenceNumber += incomingCommand -> fragmentCount - 1;
    } 

    if (currentCommand == enet_list_begin (& channel -> incomingReliableCommands))
      return;

    channel -> incomingUnreliableSequenceNumber = 0;

    enet_list_move (enet_list_end (& peer -> dispatchedCommands), enet_list_begin (& channel -> incomingReliableCommands), enet_list_previous (currentCommand));

    if (! peer -> needsDispatch)
    {
       enet_list_insert (enet_list_end (& peer -> host -> dispatchQueue), & peer -> dispatchList);

       peer -> needsDispatch = 1;
    }

    enet_peer_dispatch_incoming_unreliable_commands (peer, channel);
}