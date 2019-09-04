#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int enet_uint8 ;
typedef  size_t enet_uint32 ;
struct TYPE_21__ {int /*<<< orphan*/  reliableWindows; scalar_t__ usedReliableWindows; int /*<<< orphan*/  incomingUnreliableCommands; int /*<<< orphan*/  incomingReliableCommands; scalar_t__ incomingUnreliableSequenceNumber; scalar_t__ incomingReliableSequenceNumber; scalar_t__ outgoingUnreliableSequenceNumber; scalar_t__ outgoingReliableSequenceNumber; } ;
struct TYPE_16__ {scalar_t__ host; scalar_t__ port; } ;
struct TYPE_20__ {size_t peerCount; size_t channelLimit; size_t outgoingBandwidth; size_t incomingBandwidth; TYPE_3__ receivedAddress; TYPE_6__* peers; } ;
struct TYPE_19__ {scalar_t__ state; scalar_t__ connectID; size_t channelCount; size_t incomingBandwidth; size_t outgoingBandwidth; size_t packetThrottleInterval; size_t packetThrottleAcceleration; size_t packetThrottleDeceleration; size_t eventData; int outgoingSessionID; int incomingSessionID; size_t mtu; size_t windowSize; size_t incomingPeerID; TYPE_8__* channels; int /*<<< orphan*/  outgoingPeerID; TYPE_3__ address; } ;
struct TYPE_15__ {int incomingSessionID; int outgoingSessionID; scalar_t__ connectID; void* packetThrottleDeceleration; void* packetThrottleAcceleration; void* packetThrottleInterval; void* outgoingBandwidth; void* incomingBandwidth; void* channelCount; void* windowSize; void* mtu; void* outgoingPeerID; } ;
struct TYPE_14__ {int command; int channelID; } ;
struct TYPE_17__ {scalar_t__ connectID; int incomingSessionID; int outgoingSessionID; int /*<<< orphan*/  windowSize; int /*<<< orphan*/  mtu; int /*<<< orphan*/  data; int /*<<< orphan*/  packetThrottleDeceleration; int /*<<< orphan*/  packetThrottleAcceleration; int /*<<< orphan*/  packetThrottleInterval; int /*<<< orphan*/  outgoingBandwidth; int /*<<< orphan*/  incomingBandwidth; int /*<<< orphan*/  outgoingPeerID; int /*<<< orphan*/  channelCount; } ;
struct TYPE_18__ {TYPE_2__ verifyConnect; TYPE_1__ header; TYPE_4__ connect; } ;
typedef  int /*<<< orphan*/  ENetProtocolHeader ;
typedef  TYPE_5__ ENetProtocol ;
typedef  TYPE_6__ ENetPeer ;
typedef  TYPE_7__ ENetHost ;
typedef  TYPE_8__ ENetChannel ;

/* Variables and functions */
 void* ENET_HOST_TO_NET_16 (size_t) ; 
 void* ENET_HOST_TO_NET_32 (size_t) ; 
 size_t ENET_MAX (size_t,size_t) ; 
 size_t ENET_MIN (size_t,size_t) ; 
 int /*<<< orphan*/  ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 size_t ENET_NET_TO_HOST_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_PEER_STATE_ACKNOWLEDGING_CONNECT ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECTED ; 
 size_t ENET_PEER_WINDOW_SIZE_SCALE ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int ENET_PROTOCOL_COMMAND_VERIFY_CONNECT ; 
 int ENET_PROTOCOL_HEADER_SESSION_MASK ; 
 int ENET_PROTOCOL_HEADER_SESSION_SHIFT ; 
 size_t ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT ; 
 size_t ENET_PROTOCOL_MAXIMUM_MTU ; 
 size_t ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE ; 
 size_t ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT ; 
 size_t ENET_PROTOCOL_MINIMUM_MTU ; 
 size_t ENET_PROTOCOL_MINIMUM_WINDOW_SIZE ; 
 int /*<<< orphan*/  enet_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_malloc (size_t) ; 
 int /*<<< orphan*/  enet_peer_queue_outgoing_command (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ENetPeer *
enet_protocol_handle_connect (ENetHost * host, ENetProtocolHeader * header, ENetProtocol * command)
{
    enet_uint8 incomingSessionID, outgoingSessionID;
    enet_uint32 mtu, windowSize;
    ENetChannel * channel;
    size_t channelCount;
    ENetPeer * currentPeer;
    ENetProtocol verifyCommand;

    channelCount = ENET_NET_TO_HOST_32 (command -> connect.channelCount);

    if (channelCount < ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT ||
        channelCount > ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT)
      return NULL;

    for (currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
        if (currentPeer -> state != ENET_PEER_STATE_DISCONNECTED &&
            currentPeer -> address.host == host -> receivedAddress.host &&
            currentPeer -> address.port == host -> receivedAddress.port &&
            currentPeer -> connectID == command -> connect.connectID)
          return NULL;
    }

    for (currentPeer = host -> peers;
         currentPeer < & host -> peers [host -> peerCount];
         ++ currentPeer)
    {
        if (currentPeer -> state == ENET_PEER_STATE_DISCONNECTED)
          break;
    }

    if (currentPeer >= & host -> peers [host -> peerCount])
      return NULL;

    if (channelCount > host -> channelLimit)
      channelCount = host -> channelLimit;
    currentPeer -> channels = (ENetChannel *) enet_malloc (channelCount * sizeof (ENetChannel));
    if (currentPeer -> channels == NULL)
      return NULL;
    currentPeer -> channelCount = channelCount;
    currentPeer -> state = ENET_PEER_STATE_ACKNOWLEDGING_CONNECT;
    currentPeer -> connectID = command -> connect.connectID;
    currentPeer -> address = host -> receivedAddress;
    currentPeer -> outgoingPeerID = ENET_NET_TO_HOST_16 (command -> connect.outgoingPeerID);
    currentPeer -> incomingBandwidth = ENET_NET_TO_HOST_32 (command -> connect.incomingBandwidth);
    currentPeer -> outgoingBandwidth = ENET_NET_TO_HOST_32 (command -> connect.outgoingBandwidth);
    currentPeer -> packetThrottleInterval = ENET_NET_TO_HOST_32 (command -> connect.packetThrottleInterval);
    currentPeer -> packetThrottleAcceleration = ENET_NET_TO_HOST_32 (command -> connect.packetThrottleAcceleration);
    currentPeer -> packetThrottleDeceleration = ENET_NET_TO_HOST_32 (command -> connect.packetThrottleDeceleration);
    currentPeer -> eventData = ENET_NET_TO_HOST_32 (command -> connect.data);

    incomingSessionID = command -> connect.incomingSessionID == 0xFF ? currentPeer -> outgoingSessionID : command -> connect.incomingSessionID;
    incomingSessionID = (incomingSessionID + 1) & (ENET_PROTOCOL_HEADER_SESSION_MASK >> ENET_PROTOCOL_HEADER_SESSION_SHIFT);
    if (incomingSessionID == currentPeer -> outgoingSessionID)
      incomingSessionID = (incomingSessionID + 1) & (ENET_PROTOCOL_HEADER_SESSION_MASK >> ENET_PROTOCOL_HEADER_SESSION_SHIFT);
    currentPeer -> outgoingSessionID = incomingSessionID;

    outgoingSessionID = command -> connect.outgoingSessionID == 0xFF ? currentPeer -> incomingSessionID : command -> connect.outgoingSessionID;
    outgoingSessionID = (outgoingSessionID + 1) & (ENET_PROTOCOL_HEADER_SESSION_MASK >> ENET_PROTOCOL_HEADER_SESSION_SHIFT);
    if (outgoingSessionID == currentPeer -> incomingSessionID)
      outgoingSessionID = (outgoingSessionID + 1) & (ENET_PROTOCOL_HEADER_SESSION_MASK >> ENET_PROTOCOL_HEADER_SESSION_SHIFT);
    currentPeer -> incomingSessionID = outgoingSessionID;

    for (channel = currentPeer -> channels;
         channel < & currentPeer -> channels [channelCount];
         ++ channel)
    {
        channel -> outgoingReliableSequenceNumber = 0;
        channel -> outgoingUnreliableSequenceNumber = 0;
        channel -> incomingReliableSequenceNumber = 0;
        channel -> incomingUnreliableSequenceNumber = 0;

        enet_list_clear (& channel -> incomingReliableCommands);
        enet_list_clear (& channel -> incomingUnreliableCommands);

        channel -> usedReliableWindows = 0;
        memset (channel -> reliableWindows, 0, sizeof (channel -> reliableWindows));
    }

    mtu = ENET_NET_TO_HOST_32 (command -> connect.mtu);

    if (mtu < ENET_PROTOCOL_MINIMUM_MTU)
      mtu = ENET_PROTOCOL_MINIMUM_MTU;
    else
    if (mtu > ENET_PROTOCOL_MAXIMUM_MTU)
      mtu = ENET_PROTOCOL_MAXIMUM_MTU;

    currentPeer -> mtu = mtu;

    if (host -> outgoingBandwidth == 0 &&
        currentPeer -> incomingBandwidth == 0)
      currentPeer -> windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;
    else
    if (host -> outgoingBandwidth == 0 ||
        currentPeer -> incomingBandwidth == 0)
      currentPeer -> windowSize = (ENET_MAX (host -> outgoingBandwidth, currentPeer -> incomingBandwidth) /
                                    ENET_PEER_WINDOW_SIZE_SCALE) *
                                      ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;
    else
      currentPeer -> windowSize = (ENET_MIN (host -> outgoingBandwidth, currentPeer -> incomingBandwidth) /
                                    ENET_PEER_WINDOW_SIZE_SCALE) * 
                                      ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;

    if (currentPeer -> windowSize < ENET_PROTOCOL_MINIMUM_WINDOW_SIZE)
      currentPeer -> windowSize = ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;
    else
    if (currentPeer -> windowSize > ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE)
      currentPeer -> windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;

    if (host -> incomingBandwidth == 0)
      windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;
    else
      windowSize = (host -> incomingBandwidth / ENET_PEER_WINDOW_SIZE_SCALE) *
                     ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;

    if (windowSize > ENET_NET_TO_HOST_32 (command -> connect.windowSize))
      windowSize = ENET_NET_TO_HOST_32 (command -> connect.windowSize);

    if (windowSize < ENET_PROTOCOL_MINIMUM_WINDOW_SIZE)
      windowSize = ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;
    else
    if (windowSize > ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE)
      windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;

    verifyCommand.header.command = ENET_PROTOCOL_COMMAND_VERIFY_CONNECT | ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE;
    verifyCommand.header.channelID = 0xFF;
    verifyCommand.verifyConnect.outgoingPeerID = ENET_HOST_TO_NET_16 (currentPeer -> incomingPeerID);
    verifyCommand.verifyConnect.incomingSessionID = incomingSessionID;
    verifyCommand.verifyConnect.outgoingSessionID = outgoingSessionID;
    verifyCommand.verifyConnect.mtu = ENET_HOST_TO_NET_16 (currentPeer -> mtu);
    verifyCommand.verifyConnect.windowSize = ENET_HOST_TO_NET_32 (windowSize);
    verifyCommand.verifyConnect.channelCount = ENET_HOST_TO_NET_32 (channelCount);
    verifyCommand.verifyConnect.incomingBandwidth = ENET_HOST_TO_NET_32 (host -> incomingBandwidth);
    verifyCommand.verifyConnect.outgoingBandwidth = ENET_HOST_TO_NET_32 (host -> outgoingBandwidth);
    verifyCommand.verifyConnect.packetThrottleInterval = ENET_HOST_TO_NET_32 (currentPeer -> packetThrottleInterval);
    verifyCommand.verifyConnect.packetThrottleAcceleration = ENET_HOST_TO_NET_32 (currentPeer -> packetThrottleAcceleration);
    verifyCommand.verifyConnect.packetThrottleDeceleration = ENET_HOST_TO_NET_32 (currentPeer -> packetThrottleDeceleration);
    verifyCommand.verifyConnect.connectID = currentPeer -> connectID;

    enet_peer_queue_outgoing_command (currentPeer, & verifyCommand, NULL, 0, 0);

    return currentPeer;
}