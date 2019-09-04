#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int enet_uint32 ;
struct TYPE_20__ {int serviceTime; } ;
struct TYPE_19__ {int lastReceiveTime; int roundTripTimeVariance; int roundTripTime; scalar_t__ lowestRoundTripTime; int highestRoundTripTimeVariance; int packetThrottleEpoch; int packetThrottleInterval; scalar_t__ lastRoundTripTime; int lastRoundTripTimeVariance; int state; int /*<<< orphan*/  eventData; int /*<<< orphan*/  sentReliableCommands; int /*<<< orphan*/  outgoingUnreliableCommands; int /*<<< orphan*/  outgoingReliableCommands; scalar_t__ earliestTimeout; } ;
struct TYPE_17__ {int /*<<< orphan*/  channelID; } ;
struct TYPE_16__ {int /*<<< orphan*/  receivedReliableSequenceNumber; int /*<<< orphan*/  receivedSentTime; } ;
struct TYPE_18__ {TYPE_2__ header; TYPE_1__ acknowledge; } ;
typedef  int /*<<< orphan*/  ENetProtocolCommand ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;
typedef  TYPE_5__ ENetHost ;
typedef  int /*<<< orphan*/  ENetEvent ;

/* Variables and functions */
 int ENET_NET_TO_HOST_16 (int /*<<< orphan*/ ) ; 
#define  ENET_PEER_STATE_ACKNOWLEDGING_CONNECT 130 
#define  ENET_PEER_STATE_DISCONNECTING 129 
#define  ENET_PEER_STATE_DISCONNECT_LATER 128 
 int /*<<< orphan*/  ENET_PROTOCOL_COMMAND_DISCONNECT ; 
 int /*<<< orphan*/  ENET_PROTOCOL_COMMAND_VERIFY_CONNECT ; 
 int ENET_TIME_DIFFERENCE (int,int) ; 
 scalar_t__ ENET_TIME_LESS (int,int) ; 
 int /*<<< orphan*/  enet_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_peer_disconnect (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_peer_throttle (TYPE_4__*,int) ; 
 int /*<<< orphan*/  enet_protocol_notify_connect (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_protocol_notify_disconnect (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enet_protocol_remove_sent_reliable_command (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enet_protocol_handle_acknowledge (ENetHost * host, ENetEvent * event, ENetPeer * peer, const ENetProtocol * command)
{
    enet_uint32 roundTripTime,
           receivedSentTime,
           receivedReliableSequenceNumber;
    ENetProtocolCommand commandNumber;

    receivedSentTime = ENET_NET_TO_HOST_16 (command -> acknowledge.receivedSentTime);
    receivedSentTime |= host -> serviceTime & 0xFFFF0000;
    if ((receivedSentTime & 0x8000) > (host -> serviceTime & 0x8000))
        receivedSentTime -= 0x10000;

    if (ENET_TIME_LESS (host -> serviceTime, receivedSentTime))
      return 0;

    peer -> lastReceiveTime = host -> serviceTime;
    peer -> earliestTimeout = 0;

    roundTripTime = ENET_TIME_DIFFERENCE (host -> serviceTime, receivedSentTime);

    enet_peer_throttle (peer, roundTripTime);

    peer -> roundTripTimeVariance -= peer -> roundTripTimeVariance / 4;

    if (roundTripTime >= peer -> roundTripTime)
    {
       peer -> roundTripTime += (roundTripTime - peer -> roundTripTime) / 8;
       peer -> roundTripTimeVariance += (roundTripTime - peer -> roundTripTime) / 4;
    }
    else
    {
       peer -> roundTripTime -= (peer -> roundTripTime - roundTripTime) / 8;
       peer -> roundTripTimeVariance += (peer -> roundTripTime - roundTripTime) / 4;
    }

    if (peer -> roundTripTime < peer -> lowestRoundTripTime)
      peer -> lowestRoundTripTime = peer -> roundTripTime;

    if (peer -> roundTripTimeVariance > peer -> highestRoundTripTimeVariance) 
      peer -> highestRoundTripTimeVariance = peer -> roundTripTimeVariance;

    if (peer -> packetThrottleEpoch == 0 ||
        ENET_TIME_DIFFERENCE (host -> serviceTime, peer -> packetThrottleEpoch) >= peer -> packetThrottleInterval)
    {
        peer -> lastRoundTripTime = peer -> lowestRoundTripTime;
        peer -> lastRoundTripTimeVariance = peer -> highestRoundTripTimeVariance;
        peer -> lowestRoundTripTime = peer -> roundTripTime;
        peer -> highestRoundTripTimeVariance = peer -> roundTripTimeVariance;
        peer -> packetThrottleEpoch = host -> serviceTime;
    }

    receivedReliableSequenceNumber = ENET_NET_TO_HOST_16 (command -> acknowledge.receivedReliableSequenceNumber);

    commandNumber = enet_protocol_remove_sent_reliable_command (peer, receivedReliableSequenceNumber, command -> header.channelID);

    switch (peer -> state)
    {
    case ENET_PEER_STATE_ACKNOWLEDGING_CONNECT:
       if (commandNumber != ENET_PROTOCOL_COMMAND_VERIFY_CONNECT)
         return -1;

       enet_protocol_notify_connect (host, peer, event);
       break;

    case ENET_PEER_STATE_DISCONNECTING:
       if (commandNumber != ENET_PROTOCOL_COMMAND_DISCONNECT)
         return -1;

       enet_protocol_notify_disconnect (host, peer, event);
       break;

    case ENET_PEER_STATE_DISCONNECT_LATER:
       if (enet_list_empty (& peer -> outgoingReliableCommands) &&
           enet_list_empty (& peer -> outgoingUnreliableCommands) &&   
           enet_list_empty (& peer -> sentReliableCommands))
         enet_peer_disconnect (peer, peer -> eventData);
       break;
    }
   
    return 0;
}