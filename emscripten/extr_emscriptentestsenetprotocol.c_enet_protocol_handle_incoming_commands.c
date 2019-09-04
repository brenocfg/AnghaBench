#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_65__   TYPE_9__ ;
typedef  struct TYPE_64__   TYPE_8__ ;
typedef  struct TYPE_63__   TYPE_7__ ;
typedef  struct TYPE_62__   TYPE_6__ ;
typedef  struct TYPE_61__   TYPE_5__ ;
typedef  struct TYPE_60__   TYPE_4__ ;
typedef  struct TYPE_59__   TYPE_3__ ;
typedef  struct TYPE_58__   TYPE_2__ ;
typedef  struct TYPE_57__   TYPE_1__ ;
typedef  struct TYPE_56__   TYPE_10__ ;

/* Type definitions */
typedef  size_t enet_uint8 ;
typedef  scalar_t__ enet_uint32 ;
typedef  int enet_uint16 ;
struct TYPE_65__ {scalar_t__ type; } ;
struct TYPE_60__ {scalar_t__ host; scalar_t__ port; } ;
struct TYPE_58__ {size_t (* decompress ) (int /*<<< orphan*/ *,size_t*,size_t,size_t*,int) ;int /*<<< orphan*/ * context; } ;
struct TYPE_64__ {size_t receivedDataLength; size_t* receivedData; scalar_t__ (* checksum ) (TYPE_10__*,int) ;int peerCount; size_t** packetData; TYPE_4__ receivedAddress; TYPE_2__ compressor; TYPE_7__* peers; } ;
struct TYPE_59__ {scalar_t__ host; scalar_t__ port; } ;
struct TYPE_63__ {int state; int outgoingPeerID; size_t incomingSessionID; scalar_t__ connectID; int /*<<< orphan*/  incomingDataTotal; TYPE_3__ address; } ;
struct TYPE_57__ {int command; void* reliableSequenceNumber; } ;
struct TYPE_62__ {TYPE_1__ header; } ;
struct TYPE_61__ {void* sentTime; void* peerID; } ;
struct TYPE_56__ {size_t* data; size_t dataLength; } ;
typedef  TYPE_5__ ENetProtocolHeader ;
typedef  int /*<<< orphan*/  ENetProtocolCommandHeader ;
typedef  TYPE_6__ ENetProtocol ;
typedef  TYPE_7__ ENetPeer ;
typedef  TYPE_8__ ENetHost ;
typedef  TYPE_9__ ENetEvent ;
typedef  TYPE_10__ ENetBuffer ;

/* Variables and functions */
 scalar_t__ ENET_EVENT_TYPE_NONE ; 
 scalar_t__ ENET_HOST_BROADCAST ; 
 void* ENET_NET_TO_HOST_16 (void*) ; 
#define  ENET_PEER_STATE_ACKNOWLEDGING_CONNECT 142 
#define  ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT 141 
 int ENET_PEER_STATE_DISCONNECTED ; 
#define  ENET_PEER_STATE_DISCONNECTING 140 
 int ENET_PEER_STATE_ZOMBIE ; 
#define  ENET_PROTOCOL_COMMAND_ACKNOWLEDGE 139 
#define  ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT 138 
#define  ENET_PROTOCOL_COMMAND_CONNECT 137 
 size_t ENET_PROTOCOL_COMMAND_COUNT ; 
#define  ENET_PROTOCOL_COMMAND_DISCONNECT 136 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int ENET_PROTOCOL_COMMAND_MASK ; 
#define  ENET_PROTOCOL_COMMAND_PING 135 
#define  ENET_PROTOCOL_COMMAND_SEND_FRAGMENT 134 
#define  ENET_PROTOCOL_COMMAND_SEND_RELIABLE 133 
#define  ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE 132 
#define  ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT 131 
#define  ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED 130 
#define  ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE 129 
#define  ENET_PROTOCOL_COMMAND_VERIFY_CONNECT 128 
 int ENET_PROTOCOL_HEADER_FLAG_COMPRESSED ; 
 int ENET_PROTOCOL_HEADER_FLAG_MASK ; 
 int ENET_PROTOCOL_HEADER_FLAG_SENT_TIME ; 
 int ENET_PROTOCOL_HEADER_SESSION_MASK ; 
 int ENET_PROTOCOL_HEADER_SESSION_SHIFT ; 
 int ENET_PROTOCOL_MAXIMUM_PEER_ID ; 
 size_t* commandSizes ; 
 int /*<<< orphan*/  enet_peer_queue_acknowledgement (TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  enet_protocol_handle_acknowledge (TYPE_8__*,TYPE_9__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_protocol_handle_bandwidth_limit (TYPE_8__*,TYPE_7__*,TYPE_6__*) ; 
 TYPE_7__* enet_protocol_handle_connect (TYPE_8__*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_protocol_handle_disconnect (TYPE_8__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_protocol_handle_ping (TYPE_8__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_protocol_handle_send_fragment (TYPE_8__*,TYPE_7__*,TYPE_6__*,size_t**) ; 
 int /*<<< orphan*/  enet_protocol_handle_send_reliable (TYPE_8__*,TYPE_7__*,TYPE_6__*,size_t**) ; 
 int /*<<< orphan*/  enet_protocol_handle_send_unreliable (TYPE_8__*,TYPE_7__*,TYPE_6__*,size_t**) ; 
 int /*<<< orphan*/  enet_protocol_handle_send_unreliable_fragment (TYPE_8__*,TYPE_7__*,TYPE_6__*,size_t**) ; 
 int /*<<< orphan*/  enet_protocol_handle_send_unsequenced (TYPE_8__*,TYPE_7__*,TYPE_6__*,size_t**) ; 
 int /*<<< orphan*/  enet_protocol_handle_throttle_configure (TYPE_8__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  enet_protocol_handle_verify_connect (TYPE_8__*,TYPE_9__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (size_t*,TYPE_5__*,size_t) ; 
 size_t stub1 (int /*<<< orphan*/ *,size_t*,size_t,size_t*,int) ; 
 scalar_t__ stub2 (TYPE_10__*,int) ; 

__attribute__((used)) static int
enet_protocol_handle_incoming_commands (ENetHost * host, ENetEvent * event)
{
    ENetProtocolHeader * header;
    ENetProtocol * command;
    ENetPeer * peer;
    enet_uint8 * currentData;
    size_t headerSize;
    enet_uint16 peerID, flags;
    enet_uint8 sessionID;

    if (host -> receivedDataLength < (size_t) & ((ENetProtocolHeader *) 0) -> sentTime)
      return 0;

    header = (ENetProtocolHeader *) host -> receivedData;

    peerID = ENET_NET_TO_HOST_16 (header -> peerID);
    sessionID = (peerID & ENET_PROTOCOL_HEADER_SESSION_MASK) >> ENET_PROTOCOL_HEADER_SESSION_SHIFT;
    flags = peerID & ENET_PROTOCOL_HEADER_FLAG_MASK;
    peerID &= ~ (ENET_PROTOCOL_HEADER_FLAG_MASK | ENET_PROTOCOL_HEADER_SESSION_MASK);

    headerSize = (flags & ENET_PROTOCOL_HEADER_FLAG_SENT_TIME ? sizeof (ENetProtocolHeader) : (size_t) & ((ENetProtocolHeader *) 0) -> sentTime);
    if (host -> checksum != NULL)
      headerSize += sizeof (enet_uint32);

    if (peerID == ENET_PROTOCOL_MAXIMUM_PEER_ID)
      peer = NULL;
    else
    if (peerID >= host -> peerCount)
      return 0;
    else
    {
       peer = & host -> peers [peerID];

       if (peer -> state == ENET_PEER_STATE_DISCONNECTED ||
           peer -> state == ENET_PEER_STATE_ZOMBIE ||
           ((host -> receivedAddress.host != peer -> address.host ||
             host -> receivedAddress.port != peer -> address.port) &&
             peer -> address.host != ENET_HOST_BROADCAST) ||
           (peer -> outgoingPeerID < ENET_PROTOCOL_MAXIMUM_PEER_ID &&
            sessionID != peer -> incomingSessionID))
         return 0;
    }
 
    if (flags & ENET_PROTOCOL_HEADER_FLAG_COMPRESSED)
    {
        size_t originalSize;
        if (host -> compressor.context == NULL || host -> compressor.decompress == NULL)
          return 0;

        originalSize = host -> compressor.decompress (host -> compressor.context,
                                    host -> receivedData + headerSize, 
                                    host -> receivedDataLength - headerSize, 
                                    host -> packetData [1] + headerSize, 
                                    sizeof (host -> packetData [1]) - headerSize);
        if (originalSize <= 0 || originalSize > sizeof (host -> packetData [1]) - headerSize)
          return 0;

        memcpy (host -> packetData [1], header, headerSize);
        host -> receivedData = host -> packetData [1];
        host -> receivedDataLength = headerSize + originalSize;
    }

    if (host -> checksum != NULL)
    {
        enet_uint32 * checksum = (enet_uint32 *) & host -> receivedData [headerSize - sizeof (enet_uint32)],
                    desiredChecksum = * checksum;
        ENetBuffer buffer;

        * checksum = peer != NULL ? peer -> connectID : 0;

        buffer.data = host -> receivedData;
        buffer.dataLength = host -> receivedDataLength;

        if (host -> checksum (& buffer, 1) != desiredChecksum)
          return 0;
    }
       
    if (peer != NULL)
    {
       peer -> address.host = host -> receivedAddress.host;
       peer -> address.port = host -> receivedAddress.port;
       peer -> incomingDataTotal += host -> receivedDataLength;
    }
    
    currentData = host -> receivedData + headerSize;
  
    while (currentData < & host -> receivedData [host -> receivedDataLength])
    {
       enet_uint8 commandNumber;
       size_t commandSize;

       command = (ENetProtocol *) currentData;

       if (currentData + sizeof (ENetProtocolCommandHeader) > & host -> receivedData [host -> receivedDataLength])
         break;

       commandNumber = command -> header.command & ENET_PROTOCOL_COMMAND_MASK;
       if (commandNumber >= ENET_PROTOCOL_COMMAND_COUNT) 
         break;
       
       commandSize = commandSizes [commandNumber];
       if (commandSize == 0 || currentData + commandSize > & host -> receivedData [host -> receivedDataLength])
         break;

       currentData += commandSize;

       if (peer == NULL && commandNumber != ENET_PROTOCOL_COMMAND_CONNECT)
         break;
         
       command -> header.reliableSequenceNumber = ENET_NET_TO_HOST_16 (command -> header.reliableSequenceNumber);

       switch (command -> header.command & ENET_PROTOCOL_COMMAND_MASK)
       {
       case ENET_PROTOCOL_COMMAND_ACKNOWLEDGE:
          if (enet_protocol_handle_acknowledge (host, event, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_CONNECT:
          peer = enet_protocol_handle_connect (host, header, command);
          if (peer == NULL)
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_VERIFY_CONNECT:
          if (enet_protocol_handle_verify_connect (host, event, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_DISCONNECT:
          if (enet_protocol_handle_disconnect (host, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_PING:
          if (enet_protocol_handle_ping (host, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_SEND_RELIABLE:
          if (enet_protocol_handle_send_reliable (host, peer, command, & currentData))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
          if (enet_protocol_handle_send_unreliable (host, peer, command, & currentData))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
          if (enet_protocol_handle_send_unsequenced (host, peer, command, & currentData))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_SEND_FRAGMENT:
          if (enet_protocol_handle_send_fragment (host, peer, command, & currentData))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT:
          if (enet_protocol_handle_bandwidth_limit (host, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE:
          if (enet_protocol_handle_throttle_configure (host, peer, command))
            goto commandError;
          break;

       case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT:
          if (enet_protocol_handle_send_unreliable_fragment (host, peer, command, & currentData))
            goto commandError;
          break;

       default:
          goto commandError;
       }

       if (peer != NULL &&
           (command -> header.command & ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE) != 0)
       {
           enet_uint16 sentTime;

           if (! (flags & ENET_PROTOCOL_HEADER_FLAG_SENT_TIME))
             break;

           sentTime = ENET_NET_TO_HOST_16 (header -> sentTime);

           switch (peer -> state)
           {
           case ENET_PEER_STATE_DISCONNECTING:
           case ENET_PEER_STATE_ACKNOWLEDGING_CONNECT:
              break;

           case ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT:
              if ((command -> header.command & ENET_PROTOCOL_COMMAND_MASK) == ENET_PROTOCOL_COMMAND_DISCONNECT)
                enet_peer_queue_acknowledgement (peer, command, sentTime);
              break;

           default:   
              enet_peer_queue_acknowledgement (peer, command, sentTime);        
              break;
           }
       }
    }

commandError:
    if (event != NULL && event -> type != ENET_EVENT_TYPE_NONE)
      return 1;

    return 0;
}