#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  unsequencedWindow; scalar_t__ eventData; scalar_t__ outgoingUnsequencedGroup; scalar_t__ incomingUnsequencedGroup; int /*<<< orphan*/  windowSize; scalar_t__ outgoingReliableSequenceNumber; scalar_t__ reliableDataInTransit; TYPE_1__* host; int /*<<< orphan*/  mtu; scalar_t__ roundTripTimeVariance; void* roundTripTime; scalar_t__ highestRoundTripTimeVariance; scalar_t__ lastRoundTripTimeVariance; void* lowestRoundTripTime; void* lastRoundTripTime; int /*<<< orphan*/  packetThrottleInterval; int /*<<< orphan*/  packetThrottleDeceleration; int /*<<< orphan*/  packetThrottleAcceleration; scalar_t__ packetThrottleEpoch; scalar_t__ packetThrottleCounter; int /*<<< orphan*/  packetThrottleLimit; int /*<<< orphan*/  packetThrottle; scalar_t__ packetLossVariance; scalar_t__ packetLoss; scalar_t__ packetsLost; scalar_t__ packetsSent; scalar_t__ packetLossEpoch; scalar_t__ earliestTimeout; scalar_t__ nextTimeout; scalar_t__ lastReceiveTime; scalar_t__ lastSendTime; scalar_t__ outgoingDataTotal; scalar_t__ incomingDataTotal; scalar_t__ outgoingBandwidthThrottleEpoch; scalar_t__ incomingBandwidthThrottleEpoch; scalar_t__ outgoingBandwidth; scalar_t__ incomingBandwidth; int /*<<< orphan*/  state; scalar_t__ connectID; int /*<<< orphan*/  outgoingPeerID; } ;
struct TYPE_5__ {int /*<<< orphan*/  mtu; } ;
typedef  TYPE_2__ ENetPeer ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_PEER_DEFAULT_PACKET_THROTTLE ; 
 void* ENET_PEER_DEFAULT_ROUND_TRIP_TIME ; 
 int /*<<< orphan*/  ENET_PEER_PACKET_THROTTLE_ACCELERATION ; 
 int /*<<< orphan*/  ENET_PEER_PACKET_THROTTLE_DECELERATION ; 
 int /*<<< orphan*/  ENET_PEER_PACKET_THROTTLE_INTERVAL ; 
 int /*<<< orphan*/  ENET_PEER_PACKET_THROTTLE_SCALE ; 
 int /*<<< orphan*/  ENET_PEER_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  ENET_PROTOCOL_MAXIMUM_PEER_ID ; 
 int /*<<< orphan*/  ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE ; 
 int /*<<< orphan*/  enet_peer_reset_queues (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
enet_peer_reset (ENetPeer * peer)
{
    peer -> outgoingPeerID = ENET_PROTOCOL_MAXIMUM_PEER_ID;
    peer -> connectID = 0;

    peer -> state = ENET_PEER_STATE_DISCONNECTED;

    peer -> incomingBandwidth = 0;
    peer -> outgoingBandwidth = 0;
    peer -> incomingBandwidthThrottleEpoch = 0;
    peer -> outgoingBandwidthThrottleEpoch = 0;
    peer -> incomingDataTotal = 0;
    peer -> outgoingDataTotal = 0;
    peer -> lastSendTime = 0;
    peer -> lastReceiveTime = 0;
    peer -> nextTimeout = 0;
    peer -> earliestTimeout = 0;
    peer -> packetLossEpoch = 0;
    peer -> packetsSent = 0;
    peer -> packetsLost = 0;
    peer -> packetLoss = 0;
    peer -> packetLossVariance = 0;
    peer -> packetThrottle = ENET_PEER_DEFAULT_PACKET_THROTTLE;
    peer -> packetThrottleLimit = ENET_PEER_PACKET_THROTTLE_SCALE;
    peer -> packetThrottleCounter = 0;
    peer -> packetThrottleEpoch = 0;
    peer -> packetThrottleAcceleration = ENET_PEER_PACKET_THROTTLE_ACCELERATION;
    peer -> packetThrottleDeceleration = ENET_PEER_PACKET_THROTTLE_DECELERATION;
    peer -> packetThrottleInterval = ENET_PEER_PACKET_THROTTLE_INTERVAL;
    peer -> lastRoundTripTime = ENET_PEER_DEFAULT_ROUND_TRIP_TIME;
    peer -> lowestRoundTripTime = ENET_PEER_DEFAULT_ROUND_TRIP_TIME;
    peer -> lastRoundTripTimeVariance = 0;
    peer -> highestRoundTripTimeVariance = 0;
    peer -> roundTripTime = ENET_PEER_DEFAULT_ROUND_TRIP_TIME;
    peer -> roundTripTimeVariance = 0;
    peer -> mtu = peer -> host -> mtu;
    peer -> reliableDataInTransit = 0;
    peer -> outgoingReliableSequenceNumber = 0;
    peer -> windowSize = ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE;
    peer -> incomingUnsequencedGroup = 0;
    peer -> outgoingUnsequencedGroup = 0;
    peer -> eventData = 0;

    memset (peer -> unsequencedWindow, 0, sizeof (peer -> unsequencedWindow));
    
    enet_peer_reset_queues (peer);
}