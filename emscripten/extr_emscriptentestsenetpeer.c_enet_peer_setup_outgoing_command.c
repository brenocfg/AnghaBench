#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ outgoingUnreliableSequenceNumber; scalar_t__ outgoingReliableSequenceNumber; } ;
struct TYPE_13__ {size_t channelID; int command; void* reliableSequenceNumber; } ;
struct TYPE_12__ {void* unsequencedGroup; } ;
struct TYPE_11__ {void* unreliableSequenceNumber; } ;
struct TYPE_14__ {TYPE_3__ header; TYPE_2__ sendUnsequenced; TYPE_1__ sendUnreliable; } ;
struct TYPE_16__ {scalar_t__ fragmentOffset; TYPE_4__ command; scalar_t__ unreliableSequenceNumber; scalar_t__ reliableSequenceNumber; scalar_t__ roundTripTimeoutLimit; scalar_t__ roundTripTimeout; scalar_t__ sentTime; scalar_t__ sendAttempts; scalar_t__ fragmentLength; } ;
struct TYPE_15__ {int /*<<< orphan*/  outgoingUnreliableCommands; int /*<<< orphan*/  outgoingReliableCommands; scalar_t__ outgoingUnsequencedGroup; scalar_t__ outgoingReliableSequenceNumber; int /*<<< orphan*/  outgoingDataTotal; TYPE_7__* channels; } ;
typedef  TYPE_5__ ENetPeer ;
typedef  TYPE_6__ ENetOutgoingCommand ;
typedef  TYPE_7__ ENetChannel ;

/* Variables and functions */
 void* ENET_HOST_TO_NET_16 (scalar_t__) ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED ; 
 int ENET_PROTOCOL_COMMAND_MASK ; 
#define  ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE 129 
#define  ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED 128 
 int /*<<< orphan*/  enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ enet_protocol_command_size (int) ; 

void
enet_peer_setup_outgoing_command (ENetPeer * peer, ENetOutgoingCommand * outgoingCommand)
{
    ENetChannel * channel = & peer -> channels [outgoingCommand -> command.header.channelID];

    peer -> outgoingDataTotal += enet_protocol_command_size (outgoingCommand -> command.header.command) + outgoingCommand -> fragmentLength;

    if (outgoingCommand -> command.header.channelID == 0xFF)
    {
       ++ peer -> outgoingReliableSequenceNumber;

       outgoingCommand -> reliableSequenceNumber = peer -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE)
    {
       ++ channel -> outgoingReliableSequenceNumber;
       channel -> outgoingUnreliableSequenceNumber = 0;

       outgoingCommand -> reliableSequenceNumber = channel -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED)
    {
       ++ peer -> outgoingUnsequencedGroup;

       outgoingCommand -> reliableSequenceNumber = 0;
       outgoingCommand -> unreliableSequenceNumber = 0;
    }
    else
    {
       if (outgoingCommand -> fragmentOffset == 0)
         ++ channel -> outgoingUnreliableSequenceNumber;
        
       outgoingCommand -> reliableSequenceNumber = channel -> outgoingReliableSequenceNumber;
       outgoingCommand -> unreliableSequenceNumber = channel -> outgoingUnreliableSequenceNumber;
    }
   
    outgoingCommand -> sendAttempts = 0;
    outgoingCommand -> sentTime = 0;
    outgoingCommand -> roundTripTimeout = 0;
    outgoingCommand -> roundTripTimeoutLimit = 0;
    outgoingCommand -> command.header.reliableSequenceNumber = ENET_HOST_TO_NET_16 (outgoingCommand -> reliableSequenceNumber);

    switch (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK)
    {
    case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
        outgoingCommand -> command.sendUnreliable.unreliableSequenceNumber = ENET_HOST_TO_NET_16 (outgoingCommand -> unreliableSequenceNumber);
        break;

    case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
        outgoingCommand -> command.sendUnsequenced.unsequencedGroup = ENET_HOST_TO_NET_16 (peer -> outgoingUnsequencedGroup);
        break;
    
    default:
        break;
    }

    if (outgoingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE)
      enet_list_insert (enet_list_end (& peer -> outgoingReliableCommands), outgoingCommand);
    else
      enet_list_insert (enet_list_end (& peer -> outgoingUnreliableCommands), outgoingCommand);
}