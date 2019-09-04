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
struct TYPE_3__ {size_t channelLimit; } ;
typedef  TYPE_1__ ENetHost ;

/* Variables and functions */
 size_t ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT ; 
 size_t ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT ; 

void
enet_host_channel_limit (ENetHost * host, size_t channelLimit)
{
    if (! channelLimit || channelLimit > ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT)
      channelLimit = ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT;
    else
    if (channelLimit < ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT)
      channelLimit = ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT;

    host -> channelLimit = channelLimit;
}