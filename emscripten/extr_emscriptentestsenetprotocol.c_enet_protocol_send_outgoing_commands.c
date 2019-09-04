#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
typedef  scalar_t__ enet_uint32 ;
struct TYPE_27__ {int dataLength; int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {scalar_t__ type; } ;
struct TYPE_22__ {size_t (* compress ) (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ;int /*<<< orphan*/ * context; } ;
struct TYPE_25__ {int continueSending; size_t peerCount; int headerFlags; scalar_t__ commandCount; int bufferCount; int packetSize; scalar_t__ serviceTime; int totalSentData; int /*<<< orphan*/  totalSentPackets; TYPE_6__* buffers; int /*<<< orphan*/  socket; int /*<<< orphan*/ ** packetData; int /*<<< orphan*/  (* checksum ) (TYPE_6__*,int) ;TYPE_1__ compressor; TYPE_3__* peers; } ;
struct TYPE_24__ {scalar_t__ state; scalar_t__ lastReceiveTime; int mtu; scalar_t__ packetLossEpoch; scalar_t__ packetsSent; scalar_t__ packetsLost; int packetLossVariance; scalar_t__ packetLoss; int outgoingPeerID; int outgoingSessionID; scalar_t__ connectID; int lastSendTime; int /*<<< orphan*/  address; int /*<<< orphan*/  outgoingUnreliableCommands; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  outgoingReliableCommands; int /*<<< orphan*/  nextTimeout; int /*<<< orphan*/  acknowledgements; } ;
struct TYPE_23__ {void* peerID; void* sentTime; } ;
typedef  int /*<<< orphan*/  ENetProtocolPing ;
typedef  TYPE_2__ ENetProtocolHeader ;
typedef  TYPE_3__ ENetPeer ;
typedef  TYPE_4__ ENetHost ;
typedef  TYPE_5__ ENetEvent ;

/* Variables and functions */
 scalar_t__ ENET_EVENT_TYPE_NONE ; 
 void* ENET_HOST_TO_NET_16 (int) ; 
 scalar_t__ ENET_PEER_PACKET_LOSS_INTERVAL ; 
 scalar_t__ ENET_PEER_PACKET_LOSS_SCALE ; 
 scalar_t__ ENET_PEER_PING_INTERVAL ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTED ; 
 scalar_t__ ENET_PEER_STATE_ZOMBIE ; 
 int ENET_PROTOCOL_HEADER_FLAG_COMPRESSED ; 
 int ENET_PROTOCOL_HEADER_FLAG_SENT_TIME ; 
 int ENET_PROTOCOL_HEADER_SESSION_SHIFT ; 
 int ENET_PROTOCOL_MAXIMUM_PEER_ID ; 
 scalar_t__ ENET_TIME_DIFFERENCE (scalar_t__,scalar_t__) ; 
 scalar_t__ ENET_TIME_GREATER_EQUAL (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_ping (TYPE_3__*) ; 
 int enet_protocol_check_timeouts (TYPE_4__*,TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  enet_protocol_remove_sent_unreliable_commands (TYPE_3__*) ; 
 int /*<<< orphan*/  enet_protocol_send_acknowledgements (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ enet_protocol_send_reliable_outgoing_commands (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  enet_protocol_send_unreliable_outgoing_commands (TYPE_4__*,TYPE_3__*) ; 
 int enet_socket_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 size_t stub1 (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int) ; 

__attribute__((used)) static int
enet_protocol_send_outgoing_commands (ENetHost * host, ENetEvent * event, int checkForTimeouts)
{
    enet_uint8 headerData [sizeof (ENetProtocolHeader) + sizeof (enet_uint32)];
    ENetProtocolHeader * header = (ENetProtocolHeader *) headerData;
    ENetPeer * currentPeer;
    int sentLength;
    size_t shouldCompress = 0;
 
    host -> continueSending = 1;

    while (host -> continueSending)
    for (host -> continueSending = 0,
           currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
        if (currentPeer -> state == ENET_PEER_STATE_DISCONNECTED ||
            currentPeer -> state == ENET_PEER_STATE_ZOMBIE)
          continue;

        host -> headerFlags = 0;
        host -> commandCount = 0;
        host -> bufferCount = 1;
        host -> packetSize = sizeof (ENetProtocolHeader);

        if (! enet_list_empty (& currentPeer -> acknowledgements))
          enet_protocol_send_acknowledgements (host, currentPeer);

        if (checkForTimeouts != 0 &&
            ! enet_list_empty (& currentPeer -> sentReliableCommands) &&
            ENET_TIME_GREATER_EQUAL (host -> serviceTime, currentPeer -> nextTimeout) &&
            enet_protocol_check_timeouts (host, currentPeer, event) == 1)
        {
            if (event != NULL && event -> type != ENET_EVENT_TYPE_NONE)
              return 1;
            else
              continue;
        }

        if ((enet_list_empty (& currentPeer -> outgoingReliableCommands) ||
              enet_protocol_send_reliable_outgoing_commands (host, currentPeer)) &&
            enet_list_empty (& currentPeer -> sentReliableCommands) &&
            ENET_TIME_DIFFERENCE (host -> serviceTime, currentPeer -> lastReceiveTime) >= ENET_PEER_PING_INTERVAL &&
            currentPeer -> mtu - host -> packetSize >= sizeof (ENetProtocolPing))
        { 
            enet_peer_ping (currentPeer);
            enet_protocol_send_reliable_outgoing_commands (host, currentPeer);
        }
                      
        if (! enet_list_empty (& currentPeer -> outgoingUnreliableCommands))
          enet_protocol_send_unreliable_outgoing_commands (host, currentPeer);

        if (host -> commandCount == 0)
          continue;

        if (currentPeer -> packetLossEpoch == 0)
          currentPeer -> packetLossEpoch = host -> serviceTime;
        else
        if (ENET_TIME_DIFFERENCE (host -> serviceTime, currentPeer -> packetLossEpoch) >= ENET_PEER_PACKET_LOSS_INTERVAL &&
            currentPeer -> packetsSent > 0)
        {
           enet_uint32 packetLoss = currentPeer -> packetsLost * ENET_PEER_PACKET_LOSS_SCALE / currentPeer -> packetsSent;

#ifdef ENET_DEBUG
#ifdef WIN32
           printf (
#else
           fprintf (stderr, 
#endif
                    "peer %u: %f%%+-%f%% packet loss, %u+-%u ms round trip time, %f%% throttle, %u/%u outgoing, %u/%u incoming\n", currentPeer -> incomingPeerID, currentPeer -> packetLoss / (float) ENET_PEER_PACKET_LOSS_SCALE, currentPeer -> packetLossVariance / (float) ENET_PEER_PACKET_LOSS_SCALE, currentPeer -> roundTripTime, currentPeer -> roundTripTimeVariance, currentPeer -> packetThrottle / (float) ENET_PEER_PACKET_THROTTLE_SCALE, enet_list_size (& currentPeer -> outgoingReliableCommands), enet_list_size (& currentPeer -> outgoingUnreliableCommands), currentPeer -> channels != NULL ? enet_list_size (& currentPeer -> channels -> incomingReliableCommands) : 0, currentPeer -> channels != NULL ? enet_list_size (& currentPeer -> channels -> incomingUnreliableCommands) : 0);
#endif
          
           currentPeer -> packetLossVariance -= currentPeer -> packetLossVariance / 4;

           if (packetLoss >= currentPeer -> packetLoss)
           {
              currentPeer -> packetLoss += (packetLoss - currentPeer -> packetLoss) / 8;
              currentPeer -> packetLossVariance += (packetLoss - currentPeer -> packetLoss) / 4;
           }
           else
           {
              currentPeer -> packetLoss -= (currentPeer -> packetLoss - packetLoss) / 8;
              currentPeer -> packetLossVariance += (currentPeer -> packetLoss - packetLoss) / 4;
           }

           currentPeer -> packetLossEpoch = host -> serviceTime;
           currentPeer -> packetsSent = 0;
           currentPeer -> packetsLost = 0;
        }

        host -> buffers -> data = headerData;
        if (host -> headerFlags & ENET_PROTOCOL_HEADER_FLAG_SENT_TIME)
        {
            header -> sentTime = ENET_HOST_TO_NET_16 (host -> serviceTime & 0xFFFF);

            host -> buffers -> dataLength = sizeof (ENetProtocolHeader);
        }
        else
          host -> buffers -> dataLength = (size_t) & ((ENetProtocolHeader *) 0) -> sentTime;

        shouldCompress = 0;
        if (host -> compressor.context != NULL && host -> compressor.compress != NULL)
        {
            size_t originalSize = host -> packetSize - sizeof(ENetProtocolHeader),
                   compressedSize = host -> compressor.compress (host -> compressor.context,
                                        & host -> buffers [1], host -> bufferCount - 1,
                                        originalSize,
                                        host -> packetData [1],
                                        originalSize);
            if (compressedSize > 0 && compressedSize < originalSize)
            {
                host -> headerFlags |= ENET_PROTOCOL_HEADER_FLAG_COMPRESSED;
                shouldCompress = compressedSize;
#ifdef ENET_DEBUG_COMPRESS
#ifdef WIN32
           printf (
#else
           fprintf (stderr,
#endif
                    "peer %u: compressed %u -> %u (%u%%)\n", currentPeer -> incomingPeerID, originalSize, compressedSize, (compressedSize * 100) / originalSize);
#endif
            }
        }

        if (currentPeer -> outgoingPeerID < ENET_PROTOCOL_MAXIMUM_PEER_ID)
          host -> headerFlags |= currentPeer -> outgoingSessionID << ENET_PROTOCOL_HEADER_SESSION_SHIFT;
        header -> peerID = ENET_HOST_TO_NET_16 (currentPeer -> outgoingPeerID | host -> headerFlags);
        if (host -> checksum != NULL)
        {
            enet_uint32 * checksum = (enet_uint32 *) & headerData [host -> buffers -> dataLength];
            * checksum = currentPeer -> outgoingPeerID < ENET_PROTOCOL_MAXIMUM_PEER_ID ? currentPeer -> connectID : 0;
            host -> buffers -> dataLength += sizeof (enet_uint32);
            * checksum = host -> checksum (host -> buffers, host -> bufferCount);
        }

        if (shouldCompress > 0)
        {
            host -> buffers [1].data = host -> packetData [1];
            host -> buffers [1].dataLength = shouldCompress;
            host -> bufferCount = 2;
        }

        currentPeer -> lastSendTime = host -> serviceTime;

        sentLength = enet_socket_send (host -> socket, & currentPeer -> address, host -> buffers, host -> bufferCount);

        enet_protocol_remove_sent_unreliable_commands (currentPeer);

        if (sentLength < 0)
          return -1;

        host -> totalSentData += sentLength;
        host -> totalSentPackets ++;
    }
   
    return 0;
}