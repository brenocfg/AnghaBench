#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* enet_uint32 ;
struct TYPE_11__ {scalar_t__ state; void* packetThrottleInterval; void* packetThrottleAcceleration; void* packetThrottleDeceleration; scalar_t__ connectID; size_t channelCount; void* mtu; void* windowSize; void* outgoingBandwidth; void* incomingBandwidth; int /*<<< orphan*/  outgoingSessionID; int /*<<< orphan*/  incomingSessionID; int /*<<< orphan*/  outgoingPeerID; scalar_t__ eventData; } ;
struct TYPE_9__ {scalar_t__ connectID; int /*<<< orphan*/  outgoingBandwidth; int /*<<< orphan*/  incomingBandwidth; int /*<<< orphan*/  windowSize; int /*<<< orphan*/  mtu; int /*<<< orphan*/  outgoingSessionID; int /*<<< orphan*/  incomingSessionID; int /*<<< orphan*/  outgoingPeerID; int /*<<< orphan*/  packetThrottleDeceleration; int /*<<< orphan*/  packetThrottleAcceleration; int /*<<< orphan*/  packetThrottleInterval; int /*<<< orphan*/  channelCount; } ;
struct TYPE_10__ {TYPE_1__ verifyConnect; } ;
typedef  TYPE_2__ ENetProtocol ;
typedef  TYPE_3__ ENetPeer ;
typedef  int /*<<< orphan*/  ENetHost ;
typedef  int /*<<< orphan*/  ENetEvent ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
 void* ENET_NET_TO_HOST_32 (int /*<<< orphan*/ ) ; 
 scalar_t__ ENET_PEER_STATE_CONNECTING ; 
 int /*<<< orphan*/  ENET_PEER_STATE_ZOMBIE ; 
 size_t ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT ; 
 void* ENET_PROTOCOL_MAXIMUM_MTU ; 
 void* ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE ; 
 size_t ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT ; 
 void* ENET_PROTOCOL_MINIMUM_MTU ; 
 void* ENET_PROTOCOL_MINIMUM_WINDOW_SIZE ; 
 int /*<<< orphan*/  enet_protocol_dispatch_state (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_protocol_notify_connect (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_protocol_remove_sent_reliable_command (TYPE_3__*,int,int) ; 

__attribute__((used)) static int
enet_protocol_handle_verify_connect (ENetHost * host, ENetEvent * event, ENetPeer * peer, const ENetProtocol * command)
{
    enet_uint32 mtu, windowSize;
    size_t channelCount;

    if (peer -> state != ENET_PEER_STATE_CONNECTING)
      return 0;

    channelCount = ENET_NET_TO_HOST_32 (command -> verifyConnect.channelCount);

    if (channelCount < ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT || channelCount > ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT ||
        ENET_NET_TO_HOST_32 (command -> verifyConnect.packetThrottleInterval) != peer -> packetThrottleInterval ||
        ENET_NET_TO_HOST_32 (command -> verifyConnect.packetThrottleAcceleration) != peer -> packetThrottleAcceleration ||
        ENET_NET_TO_HOST_32 (command -> verifyConnect.packetThrottleDeceleration) != peer -> packetThrottleDeceleration ||
        command -> verifyConnect.connectID != peer -> connectID)
    {
        peer -> eventData = 0;

        enet_protocol_dispatch_state (host, peer, ENET_PEER_STATE_ZOMBIE);

        return -1;
    }

    enet_protocol_remove_sent_reliable_command (peer, 1, 0xFF);
    
    if (channelCount < peer -> channelCount)
      peer -> channelCount = channelCount;

    peer -> outgoingPeerID = ENET_NET_TO_HOST_16 (command -> verifyConnect.outgoingPeerID);
    peer -> incomingSessionID = command -> verifyConnect.incomingSessionID;
    peer -> outgoingSessionID = command -> verifyConnect.outgoingSessionID;

    mtu = ENET_NET_TO_HOST_32 (command -> verifyConnect.mtu);

    if (mtu < ENET_PROTOCOL_MINIMUM_MTU)
      mtu = ENET_PROTOCOL_MINIMUM_MTU;
    else 
    if (mtu > ENET_PROTOCOL_MAXIMUM_MTU)
      mtu = ENET_PROTOCOL_MAXIMUM_MTU;

    if (mtu < peer -> mtu)
      peer -> mtu = mtu;

    windowSize = ENET_NET_TO_HOST_32 (command -> verifyConnect.windowSize);

    if (windowSize < ENET_PROTOCOL_MINIMUM_WINDOW_SIZE)
      windowSize = ENET_PROTOCOL_MINIMUM_WINDOW_SIZE;

    if (windowSize > ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE)
      windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;

    if (windowSize < peer -> windowSize)
      peer -> windowSize = windowSize;

    peer -> incomingBandwidth = ENET_NET_TO_HOST_32 (command -> verifyConnect.incomingBandwidth);
    peer -> outgoingBandwidth = ENET_NET_TO_HOST_32 (command -> verifyConnect.outgoingBandwidth);

    enet_protocol_notify_connect (host, peer, event);
    return 0;
}