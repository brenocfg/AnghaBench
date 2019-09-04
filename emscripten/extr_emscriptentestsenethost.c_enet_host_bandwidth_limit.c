#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* enet_uint32 ;
struct TYPE_3__ {int recalculateBandwidthLimits; void* outgoingBandwidth; void* incomingBandwidth; } ;
typedef  TYPE_1__ ENetHost ;

/* Variables and functions */

void
enet_host_bandwidth_limit (ENetHost * host, enet_uint32 incomingBandwidth, enet_uint32 outgoingBandwidth)
{
    host -> incomingBandwidth = incomingBandwidth;
    host -> outgoingBandwidth = outgoingBandwidth;
    host -> recalculateBandwidthLimits = 1;
}