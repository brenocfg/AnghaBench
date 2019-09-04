#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* packetThrottleDeceleration; void* packetThrottleAcceleration; void* packetThrottleInterval; } ;
struct TYPE_6__ {int /*<<< orphan*/  packetThrottleDeceleration; int /*<<< orphan*/  packetThrottleAcceleration; int /*<<< orphan*/  packetThrottleInterval; } ;
struct TYPE_7__ {TYPE_1__ throttleConfigure; } ;
typedef  TYPE_2__ ENetProtocol ;
typedef  TYPE_3__ ENetPeer ;
typedef  int /*<<< orphan*/  ENetHost ;

/* Variables and functions */
 void* ENET_NET_TO_HOST_32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enet_protocol_handle_throttle_configure (ENetHost * host, ENetPeer * peer, const ENetProtocol * command)
{
    peer -> packetThrottleInterval = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleInterval);
    peer -> packetThrottleAcceleration = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleAcceleration);
    peer -> packetThrottleDeceleration = ENET_NET_TO_HOST_32 (command -> throttleConfigure.packetThrottleDeceleration);

    return 0;
}