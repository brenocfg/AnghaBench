#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int enet_uint32 ;
typedef  int enet_uint16 ;
struct TYPE_25__ {int incomingReliableSequenceNumber; int incomingUnreliableSequenceNumber; int /*<<< orphan*/  incomingUnreliableCommands; int /*<<< orphan*/  incomingReliableCommands; } ;
struct TYPE_20__ {size_t channelID; int command; int reliableSequenceNumber; } ;
struct TYPE_19__ {int /*<<< orphan*/  unreliableSequenceNumber; } ;
struct TYPE_21__ {TYPE_2__ header; TYPE_1__ sendUnreliable; } ;
struct TYPE_24__ {int reliableSequenceNumber; int unreliableSequenceNumber; int fragmentCount; int fragmentsRemaining; int* fragments; TYPE_5__* packet; TYPE_3__ command; } ;
struct TYPE_23__ {scalar_t__ referenceCount; } ;
struct TYPE_22__ {scalar_t__ state; TYPE_7__* channels; } ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;
typedef  TYPE_5__ ENetPacket ;
typedef  scalar_t__ ENetListIterator ;
typedef  TYPE_6__ ENetIncomingCommand ;
typedef  TYPE_7__ ENetChannel ;

/* Variables and functions */
 int ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 int ENET_PEER_FREE_RELIABLE_WINDOWS ; 
 scalar_t__ ENET_PEER_RELIABLE_WINDOWS ; 
 int ENET_PEER_RELIABLE_WINDOW_SIZE ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 int ENET_PROTOCOL_COMMAND_MASK ; 
#define  ENET_PROTOCOL_COMMAND_SEND_FRAGMENT 132 
#define  ENET_PROTOCOL_COMMAND_SEND_RELIABLE 131 
#define  ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE 130 
#define  ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT 129 
#define  ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED 128 
 int ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT ; 
 int /*<<< orphan*/  enet_free (TYPE_6__*) ; 
 scalar_t__ enet_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_list_insert (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_list_next (scalar_t__) ; 
 scalar_t__ enet_list_previous (scalar_t__) ; 
 scalar_t__ enet_malloc (int) ; 
 int /*<<< orphan*/  enet_packet_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  enet_peer_dispatch_incoming_reliable_commands (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  enet_peer_dispatch_incoming_unreliable_commands (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

ENetIncomingCommand *
enet_peer_queue_incoming_command (ENetPeer * peer, const ENetProtocol * command, ENetPacket * packet, enet_uint32 fragmentCount)
{
    static ENetIncomingCommand dummyCommand;

    ENetChannel * channel = & peer -> channels [command -> header.channelID];
    enet_uint32 unreliableSequenceNumber = 0, reliableSequenceNumber = 0;
    enet_uint16 reliableWindow, currentWindow;
    ENetIncomingCommand * incomingCommand;
    ENetListIterator currentCommand;

    if (peer -> state == ENET_PEER_STATE_DISCONNECT_LATER)
      goto freePacket;

    if ((command -> header.command & ENET_PROTOCOL_COMMAND_MASK) != ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED)
    {
        reliableSequenceNumber = command -> header.reliableSequenceNumber;
        reliableWindow = reliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;
        currentWindow = channel -> incomingReliableSequenceNumber / ENET_PEER_RELIABLE_WINDOW_SIZE;

        if (reliableSequenceNumber < channel -> incomingReliableSequenceNumber)
           reliableWindow += ENET_PEER_RELIABLE_WINDOWS;

        if (reliableWindow < currentWindow || reliableWindow >= currentWindow + ENET_PEER_FREE_RELIABLE_WINDOWS - 1)
          goto freePacket;
    }
                    
    switch (command -> header.command & ENET_PROTOCOL_COMMAND_MASK)
    {
    case ENET_PROTOCOL_COMMAND_SEND_FRAGMENT:
    case ENET_PROTOCOL_COMMAND_SEND_RELIABLE:
       if (reliableSequenceNumber == channel -> incomingReliableSequenceNumber)
         goto freePacket;
       
       for (currentCommand = enet_list_previous (enet_list_end (& channel -> incomingReliableCommands));
            currentCommand != enet_list_end (& channel -> incomingReliableCommands);
            currentCommand = enet_list_previous (currentCommand))
       {
          incomingCommand = (ENetIncomingCommand *) currentCommand;

          if (reliableSequenceNumber >= channel -> incomingReliableSequenceNumber)
          {
             if (incomingCommand -> reliableSequenceNumber < channel -> incomingReliableSequenceNumber)
               continue;
          }
          else
          if (incomingCommand -> reliableSequenceNumber >= channel -> incomingReliableSequenceNumber)
            break;

          if (incomingCommand -> reliableSequenceNumber <= reliableSequenceNumber)
          {
             if (incomingCommand -> reliableSequenceNumber < reliableSequenceNumber)
               break;

             goto freePacket;
          }
       }
       break;

    case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
    case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT:
       unreliableSequenceNumber = ENET_NET_TO_HOST_16 (command -> sendUnreliable.unreliableSequenceNumber);

       if (reliableSequenceNumber == channel -> incomingReliableSequenceNumber && 
           unreliableSequenceNumber <= channel -> incomingUnreliableSequenceNumber)
         goto freePacket;

       for (currentCommand = enet_list_previous (enet_list_end (& channel -> incomingUnreliableCommands));
            currentCommand != enet_list_end (& channel -> incomingUnreliableCommands);
            currentCommand = enet_list_previous (currentCommand))
       {
          incomingCommand = (ENetIncomingCommand *) currentCommand;

          if ((command -> header.command & ENET_PROTOCOL_COMMAND_MASK) == ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED)
            continue;

          if (reliableSequenceNumber >= channel -> incomingReliableSequenceNumber)
          {
             if (incomingCommand -> reliableSequenceNumber < channel -> incomingReliableSequenceNumber)
               continue;
          }
          else
          if (incomingCommand -> reliableSequenceNumber >= channel -> incomingReliableSequenceNumber)
            break;

          if (incomingCommand -> reliableSequenceNumber < reliableSequenceNumber)
            break;

          if (incomingCommand -> reliableSequenceNumber > reliableSequenceNumber)
            continue;

          if (incomingCommand -> unreliableSequenceNumber <= unreliableSequenceNumber)
          {
             if (incomingCommand -> unreliableSequenceNumber < unreliableSequenceNumber)
               break;

             goto freePacket;
          }
       }
       break;

    case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
       currentCommand = enet_list_end (& channel -> incomingUnreliableCommands);
       break;

    default:
       goto freePacket;
    }

    incomingCommand = (ENetIncomingCommand *) enet_malloc (sizeof (ENetIncomingCommand));
    if (incomingCommand == NULL)
      goto notifyError;

    incomingCommand -> reliableSequenceNumber = command -> header.reliableSequenceNumber;
    incomingCommand -> unreliableSequenceNumber = unreliableSequenceNumber & 0xFFFF;
    incomingCommand -> command = * command;
    incomingCommand -> fragmentCount = fragmentCount;
    incomingCommand -> fragmentsRemaining = fragmentCount;
    incomingCommand -> packet = packet;
    incomingCommand -> fragments = NULL;
    
    if (fragmentCount > 0)
    { 
       if (fragmentCount <= ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT)
         incomingCommand -> fragments = (enet_uint32 *) enet_malloc ((fragmentCount + 31) / 32 * sizeof (enet_uint32));
       if (incomingCommand -> fragments == NULL)
       {
          enet_free (incomingCommand);

          goto notifyError;
       }
       memset (incomingCommand -> fragments, 0, (fragmentCount + 31) / 32 * sizeof (enet_uint32));
    }

    if (packet != NULL)
      ++ packet -> referenceCount;

    enet_list_insert (enet_list_next (currentCommand), incomingCommand);

    switch (command -> header.command & ENET_PROTOCOL_COMMAND_MASK)
    {
    case ENET_PROTOCOL_COMMAND_SEND_FRAGMENT:
    case ENET_PROTOCOL_COMMAND_SEND_RELIABLE:
       enet_peer_dispatch_incoming_reliable_commands (peer, channel);
       break;

    default:
       enet_peer_dispatch_incoming_unreliable_commands (peer, channel);
       break;
    }

    return incomingCommand;

freePacket:
    if (fragmentCount > 0)
      goto notifyError;

    if (packet != NULL && packet -> referenceCount == 0)
      enet_packet_destroy (packet);

    return & dummyCommand;

notifyError:
    if (packet != NULL && packet -> referenceCount == 0)
      enet_packet_destroy (packet);

    return NULL;
}