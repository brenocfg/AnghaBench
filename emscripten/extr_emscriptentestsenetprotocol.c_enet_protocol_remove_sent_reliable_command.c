#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ enet_uint8 ;
typedef  size_t enet_uint16 ;
struct TYPE_14__ {scalar_t__ referenceCount; } ;
struct TYPE_13__ {scalar_t__* reliableWindows; int usedReliableWindows; } ;
struct TYPE_9__ {scalar_t__ channelID; int command; } ;
struct TYPE_10__ {TYPE_1__ header; } ;
struct TYPE_12__ {size_t reliableSequenceNumber; int sendAttempts; scalar_t__ roundTripTimeout; scalar_t__ sentTime; TYPE_7__* packet; scalar_t__ fragmentLength; int /*<<< orphan*/  outgoingCommandList; TYPE_2__ command; } ;
struct TYPE_11__ {scalar_t__ channelCount; scalar_t__ nextTimeout; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  reliableDataInTransit; TYPE_5__* channels; int /*<<< orphan*/  outgoingReliableCommands; } ;
typedef  scalar_t__ ENetProtocolCommand ;
typedef  TYPE_3__ ENetPeer ;
typedef  TYPE_4__ ENetOutgoingCommand ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_5__ ENetChannel ;

/* Variables and functions */
 size_t ENET_PEER_RELIABLE_WINDOW_SIZE ; 
 int ENET_PROTOCOL_COMMAND_MASK ; 
 scalar_t__ ENET_PROTOCOL_COMMAND_NONE ; 
 int /*<<< orphan*/  enet_free (TYPE_4__*) ; 
 scalar_t__ enet_list_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_front (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_next (scalar_t__) ; 
 int /*<<< orphan*/  enet_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_7__*) ; 

__attribute__((used)) static ENetProtocolCommand
enet_protocol_remove_sent_reliable_command (ENetPeer * peer, enet_uint16 reliableSequenceNumber, enet_uint8 channelID)
{
    ENetOutgoingCommand * outgoingCommand = NULL;
    ENetListIterator currentCommand;
    ENetProtocolCommand commandNumber;
    int wasSent = 1;

    for (currentCommand = enet_list_begin (& peer -> sentReliableCommands);
         currentCommand != enet_list_end (& peer -> sentReliableCommands);
         currentCommand = enet_list_next (currentCommand))
    {
       outgoingCommand = (ENetOutgoingCommand *) currentCommand;
        
       if (outgoingCommand -> reliableSequenceNumber == reliableSequenceNumber &&
           outgoingCommand -> command.header.channelID == channelID)
         break;
    }

    if (currentCommand == enet_list_end (& peer -> sentReliableCommands))
    {
       for (currentCommand = enet_list_begin (& peer -> outgoingReliableCommands);
            currentCommand != enet_list_end (& peer -> outgoingReliableCommands);
            currentCommand = enet_list_next (currentCommand))
       {
          outgoingCommand = (ENetOutgoingCommand *) currentCommand;

          if (outgoingCommand -> sendAttempts < 1) return ENET_PROTOCOL_COMMAND_NONE;

          if (outgoingCommand -> reliableSequenceNumber == reliableSequenceNumber &&
              outgoingCommand -> command.header.channelID == channelID)
            break;
       }

       if (currentCommand == enet_list_end (& peer -> outgoingReliableCommands))
         return ENET_PROTOCOL_COMMAND_NONE;

       wasSent = 0;
    }

    if (channelID < peer -> channelCount)
    {
       ENetChannel * channel = & peer -> channels [channelID];
       enet_uint16 reliableWindow = reliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;
       if (channel -> reliableWindows [reliableWindow] > 0)
       {
          -- channel -> reliableWindows [reliableWindow];
          if (! channel -> reliableWindows [reliableWindow])
            channel -> usedReliableWindows &= ~ (1 << reliableWindow);
       }
    }

    commandNumber = (ENetProtocolCommand) (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK);
    
    enet_list_remove (& outgoingCommand -> outgoingCommandList);

    if (outgoingCommand -> packet != NULL)
    {
       if (wasSent)
         peer -> reliableDataInTransit -= outgoingCommand -> fragmentLength;

       -- outgoingCommand -> packet -> referenceCount;

       if (outgoingCommand -> packet -> referenceCount == 0)
         enet_packet_destroy (outgoingCommand -> packet);
    }

    enet_free (outgoingCommand);

    if (enet_list_empty (& peer -> sentReliableCommands))
      return commandNumber;
    
    outgoingCommand = (ENetOutgoingCommand *) enet_list_front (& peer -> sentReliableCommands);
    
    peer -> nextTimeout = outgoingCommand -> sentTime + outgoingCommand -> roundTripTimeout;

    return commandNumber;
}