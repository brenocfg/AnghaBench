#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ enet_uint32 ;
struct TYPE_13__ {scalar_t__ bandwidthThrottleEpoch; size_t peerCount; scalar_t__ outgoingBandwidth; scalar_t__ incomingBandwidth; TYPE_4__* peers; scalar_t__ recalculateBandwidthLimits; } ;
struct TYPE_12__ {scalar_t__ state; scalar_t__ outgoingDataTotal; scalar_t__ incomingBandwidth; scalar_t__ outgoingBandwidthThrottleEpoch; int packetThrottleLimit; int packetThrottle; scalar_t__ incomingBandwidthThrottleEpoch; scalar_t__ outgoingBandwidth; scalar_t__ incomingDataTotal; } ;
struct TYPE_10__ {void* incomingBandwidth; void* outgoingBandwidth; } ;
struct TYPE_9__ {int command; int channelID; } ;
struct TYPE_11__ {TYPE_2__ bandwidthLimit; TYPE_1__ header; } ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;
typedef  TYPE_5__ ENetHost ;

/* Variables and functions */
 scalar_t__ ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL ; 
 void* ENET_HOST_TO_NET_32 (scalar_t__) ; 
 scalar_t__ ENET_PEER_PACKET_THROTTLE_SCALE ; 
 scalar_t__ ENET_PEER_STATE_CONNECTED ; 
 scalar_t__ ENET_PEER_STATE_DISCONNECT_LATER ; 
 int ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int /*<<< orphan*/  enet_peer_queue_outgoing_command (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enet_time_get () ; 

void
enet_host_bandwidth_throttle (ENetHost * host)
{
    enet_uint32 timeCurrent = enet_time_get (),
           elapsedTime = timeCurrent - host -> bandwidthThrottleEpoch,
           peersTotal = 0,
           dataTotal = 0,
           peersRemaining,
           bandwidth,
           throttle = 0,
           bandwidthLimit = 0;
    int needsAdjustment;
    ENetPeer * peer;
    ENetProtocol command;

    if (elapsedTime < ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL)
      return;

    for (peer = host -> peers;
         peer < & host -> peers [host -> peerCount];
         ++ peer)
    {
        if (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER)
          continue;

        ++ peersTotal;
        dataTotal += peer -> outgoingDataTotal;
    }

    if (peersTotal == 0)
      return;

    peersRemaining = peersTotal;
    needsAdjustment = 1;

    if (host -> outgoingBandwidth == 0)
      bandwidth = ~0;
    else
      bandwidth = (host -> outgoingBandwidth * elapsedTime) / 1000;

    while (peersRemaining > 0 && needsAdjustment != 0)
    {
        needsAdjustment = 0;
        
        if (dataTotal < bandwidth)
          throttle = ENET_PEER_PACKET_THROTTLE_SCALE;
        else
          throttle = (bandwidth * ENET_PEER_PACKET_THROTTLE_SCALE) / dataTotal;

        for (peer = host -> peers;
             peer < & host -> peers [host -> peerCount];
             ++ peer)
        {
            enet_uint32 peerBandwidth;
            
            if ((peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER) ||
                peer -> incomingBandwidth == 0 ||
                peer -> outgoingBandwidthThrottleEpoch == timeCurrent)
              continue;

            peerBandwidth = (peer -> incomingBandwidth * elapsedTime) / 1000;
            if ((throttle * peer -> outgoingDataTotal) / ENET_PEER_PACKET_THROTTLE_SCALE <= peerBandwidth)
              continue;

            peer -> packetThrottleLimit = (peerBandwidth * 
                                            ENET_PEER_PACKET_THROTTLE_SCALE) / peer -> outgoingDataTotal;
            
            if (peer -> packetThrottleLimit == 0)
              peer -> packetThrottleLimit = 1;
            
            if (peer -> packetThrottle > peer -> packetThrottleLimit)
              peer -> packetThrottle = peer -> packetThrottleLimit;

            peer -> outgoingBandwidthThrottleEpoch = timeCurrent;

            
            needsAdjustment = 1;
            -- peersRemaining;
            bandwidth -= peerBandwidth;
            dataTotal -= peerBandwidth;
        }
    }

    if (peersRemaining > 0)
    for (peer = host -> peers;
         peer < & host -> peers [host -> peerCount];
         ++ peer)
    {
        if ((peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER) ||
            peer -> outgoingBandwidthThrottleEpoch == timeCurrent)
          continue;

        peer -> packetThrottleLimit = throttle;

        if (peer -> packetThrottle > peer -> packetThrottleLimit)
          peer -> packetThrottle = peer -> packetThrottleLimit;
    }
    
    if (host -> recalculateBandwidthLimits)
    {
       host -> recalculateBandwidthLimits = 0;

       peersRemaining = peersTotal;
       bandwidth = host -> incomingBandwidth;
       needsAdjustment = 1;

       if (bandwidth == 0)
         bandwidthLimit = 0;
       else
       while (peersRemaining > 0 && needsAdjustment != 0)
       {
           needsAdjustment = 0;
           bandwidthLimit = bandwidth / peersRemaining;

           for (peer = host -> peers;
                peer < & host -> peers [host -> peerCount];
                ++ peer)
           {
               if ((peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER) ||
                   peer -> incomingBandwidthThrottleEpoch == timeCurrent)
                 continue;

               if (peer -> outgoingBandwidth > 0 &&
                   peer -> outgoingBandwidth >= bandwidthLimit)
                 continue;

               peer -> incomingBandwidthThrottleEpoch = timeCurrent;
 
               needsAdjustment = 1;
               -- peersRemaining;
               bandwidth -= peer -> outgoingBandwidth;
           }
       }

       for (peer = host -> peers;
            peer < & host -> peers [host -> peerCount];
            ++ peer)
       {
           if (peer -> state != ENET_PEER_STATE_CONNECTED && peer -> state != ENET_PEER_STATE_DISCONNECT_LATER)
             continue;

           command.header.command = ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT | ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE;
           command.header.channelID = 0xFF;
           command.bandwidthLimit.outgoingBandwidth = ENET_HOST_TO_NET_32 (host -> outgoingBandwidth);

           if (peer -> incomingBandwidthThrottleEpoch == timeCurrent)
             command.bandwidthLimit.incomingBandwidth = ENET_HOST_TO_NET_32 (peer -> outgoingBandwidth);
           else
             command.bandwidthLimit.incomingBandwidth = ENET_HOST_TO_NET_32 (bandwidthLimit);

           enet_peer_queue_outgoing_command (peer, & command, NULL, 0, 0);
       } 
    }

    host -> bandwidthThrottleEpoch = timeCurrent;

    for (peer = host -> peers;
         peer < & host -> peers [host -> peerCount];
         ++ peer)
    {
        peer -> incomingDataTotal = 0;
        peer -> outgoingDataTotal = 0;
    }
}