#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* enet_uint32 ;
struct TYPE_11__ {void* packetThrottleDeceleration; void* packetThrottleAcceleration; void* packetThrottleInterval; } ;
struct TYPE_9__ {void* packetThrottleDeceleration; void* packetThrottleAcceleration; void* packetThrottleInterval; } ;
struct TYPE_8__ {int command; int channelID; } ;
struct TYPE_10__ {TYPE_2__ throttleConfigure; TYPE_1__ header; } ;
typedef  TYPE_3__ ENetProtocol ;
typedef  TYPE_4__ ENetPeer ;

/* Variables and functions */
 void* ENET_HOST_TO_NET_32 (void*) ; 
 int ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE ; 
 int ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE ; 
 int /*<<< orphan*/  enet_peer_queue_outgoing_command (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
enet_peer_throttle_configure (ENetPeer * peer, enet_uint32 interval, enet_uint32 acceleration, enet_uint32 deceleration)
{
    ENetProtocol command;

    peer -> packetThrottleInterval = interval;
    peer -> packetThrottleAcceleration = acceleration;
    peer -> packetThrottleDeceleration = deceleration;

    command.header.command = ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE | ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE;
    command.header.channelID = 0xFF;

    command.throttleConfigure.packetThrottleInterval = ENET_HOST_TO_NET_32 (interval);
    command.throttleConfigure.packetThrottleAcceleration = ENET_HOST_TO_NET_32 (acceleration);
    command.throttleConfigure.packetThrottleDeceleration = ENET_HOST_TO_NET_32 (deceleration);

    enet_peer_queue_outgoing_command (peer, & command, NULL, 0, 0);
}