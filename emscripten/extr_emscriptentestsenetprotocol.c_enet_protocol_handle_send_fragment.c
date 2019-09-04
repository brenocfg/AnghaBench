#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
typedef  scalar_t__ enet_uint32 ;
typedef  int enet_uint16 ;
struct TYPE_28__ {size_t receivedDataLength; int /*<<< orphan*/ * receivedData; } ;
struct TYPE_21__ {int command; } ;
struct TYPE_22__ {TYPE_2__ header; } ;
struct TYPE_27__ {scalar_t__ reliableSequenceNumber; scalar_t__ fragmentCount; int* fragments; scalar_t__ fragmentsRemaining; TYPE_5__* packet; TYPE_3__ command; } ;
struct TYPE_26__ {size_t channelCount; scalar_t__ state; TYPE_10__* channels; } ;
struct TYPE_23__ {size_t channelID; scalar_t__ reliableSequenceNumber; } ;
struct TYPE_20__ {int /*<<< orphan*/  totalLength; int /*<<< orphan*/  fragmentOffset; int /*<<< orphan*/  fragmentCount; int /*<<< orphan*/  fragmentNumber; int /*<<< orphan*/  startSequenceNumber; int /*<<< orphan*/  dataLength; } ;
struct TYPE_25__ {TYPE_4__ header; TYPE_1__ sendFragment; } ;
struct TYPE_24__ {scalar_t__ dataLength; scalar_t__ data; } ;
struct TYPE_19__ {scalar_t__ incomingReliableSequenceNumber; int /*<<< orphan*/  incomingReliableCommands; } ;
typedef  int /*<<< orphan*/  ENetProtocolSendFragment ;
typedef  TYPE_6__ ENetProtocol ;
typedef  TYPE_7__ ENetPeer ;
typedef  int /*<<< orphan*/  ENetPacket ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_8__ ENetIncomingCommand ;
typedef  TYPE_9__ ENetHost ;
typedef  TYPE_10__ ENetChannel ;

/* Variables and functions */
 scalar_t__ ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_NET_TO_HOST_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_PACKET_FLAG_RELIABLE ; 
 int ENET_PEER_FREE_RELIABLE_WINDOWS ; 
 scalar_t__ ENET_PEER_RELIABLE_WINDOWS ; 
 scalar_t__ ENET_PEER_RELIABLE_WINDOW_SIZE ; 
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 int ENET_PROTOCOL_COMMAND_MASK ; 
 int ENET_PROTOCOL_COMMAND_SEND_FRAGMENT ; 
 scalar_t__ ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT ; 
 scalar_t__ ENET_PROTOCOL_MAXIMUM_PACKET_SIZE ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_list_previous (scalar_t__) ; 
 int /*<<< orphan*/ * enet_packet_create (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_peer_dispatch_incoming_reliable_commands (TYPE_7__*,TYPE_10__*) ; 
 TYPE_8__* enet_peer_queue_incoming_command (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
enet_protocol_handle_send_fragment (ENetHost * host, ENetPeer * peer, const ENetProtocol * command, enet_uint8 ** currentData)
{
    enet_uint32 fragmentNumber,
           fragmentCount,
           fragmentOffset,
           fragmentLength,
           startSequenceNumber,
           totalLength;
    ENetChannel * channel;
    enet_uint16 startWindow, currentWindow;
    ENetListIterator currentCommand;
    ENetIncomingCommand * startCommand = NULL;

    if (command -> header.channelID >= peer -> channelCount ||
        (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER))
      return -1;

    fragmentLength = ENET_NET_TO_HOST_16 (command -> sendFragment.dataLength);
    * currentData += fragmentLength;
    if (fragmentLength > ENET_PROTOCOL_MAXIMUM_PACKET_SIZE ||
        * currentData < host -> receivedData ||
        * currentData > & host -> receivedData [host -> receivedDataLength])
      return -1;

    channel = & peer -> channels [command -> header.channelID];
    startSequenceNumber = ENET_NET_TO_HOST_16 (command -> sendFragment.startSequenceNumber);
    startWindow = startSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;
    currentWindow = channel -> incomingReliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;

    if (startSequenceNumber < channel -> incomingReliableSequenceNumber)
      startWindow += ENET_PEER_RELIABLE_WINDOWS;

    if (startWindow < currentWindow || startWindow >= currentWindow + ENET_PEER_FREE_RELIABLE_WINDOWS - 1)
      return 0;

    fragmentNumber = ENET_NET_TO_HOST_32 (command -> sendFragment.fragmentNumber);
    fragmentCount = ENET_NET_TO_HOST_32 (command -> sendFragment.fragmentCount);
    fragmentOffset = ENET_NET_TO_HOST_32 (command -> sendFragment.fragmentOffset);
    totalLength = ENET_NET_TO_HOST_32 (command -> sendFragment.totalLength);
    
    if (fragmentCount > ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT ||
        fragmentNumber >= fragmentCount ||
        totalLength > ENET_PROTOCOL_MAXIMUM_PACKET_SIZE ||
        fragmentOffset >= totalLength ||
        fragmentLength > totalLength - fragmentOffset)
      return -1;
 
    for (currentCommand = enet_list_previous (enet_list_end (& channel -> incomingReliableCommands));
         currentCommand != enet_list_end (& channel -> incomingReliableCommands);
         currentCommand = enet_list_previous (currentCommand))
    {
       ENetIncomingCommand * incomingCommand = (ENetIncomingCommand *) currentCommand;

       if (startSequenceNumber >= channel -> incomingReliableSequenceNumber)
       {
          if (incomingCommand -> reliableSequenceNumber < channel -> incomingReliableSequenceNumber)
            continue;
       }
       else
       if (incomingCommand -> reliableSequenceNumber >= channel -> incomingReliableSequenceNumber)
         break;

       if (incomingCommand -> reliableSequenceNumber <= startSequenceNumber)
       {
          if (incomingCommand -> reliableSequenceNumber < startSequenceNumber)
            break;
        
          if ((incomingCommand -> command.header.command & ENET_PROTOCOL_COMMAND_MASK) != ENET_PROTOCOL_COMMAND_SEND_FRAGMENT ||
              totalLength != incomingCommand -> packet -> dataLength ||
              fragmentCount != incomingCommand -> fragmentCount)
            return -1;

          startCommand = incomingCommand;
          break;
       }
    }
 
    if (startCommand == NULL)
    {
       ENetProtocol hostCommand = * command;
       ENetPacket * packet = enet_packet_create (NULL, totalLength, ENET_PACKET_FLAG_RELIABLE);
       if (packet == NULL)
         return -1;

       hostCommand.header.reliableSequenceNumber = startSequenceNumber;

       startCommand = enet_peer_queue_incoming_command (peer, & hostCommand, packet, fragmentCount);
       if (startCommand == NULL)
         return -1;
    }
    
    if ((startCommand -> fragments [fragmentNumber / 32] & (1 << (fragmentNumber % 32))) == 0)
    {
       -- startCommand -> fragmentsRemaining;

       startCommand -> fragments [fragmentNumber / 32] |= (1 << (fragmentNumber % 32));

       if (fragmentOffset + fragmentLength > startCommand -> packet -> dataLength)
         fragmentLength = startCommand -> packet -> dataLength - fragmentOffset;

       memcpy (startCommand -> packet -> data + fragmentOffset,
               (enet_uint8 *) command + sizeof (ENetProtocolSendFragment),
               fragmentLength);

        if (startCommand -> fragmentsRemaining <= 0)
          enet_peer_dispatch_incoming_reliable_commands (peer, channel);
    }

    return 0;
}