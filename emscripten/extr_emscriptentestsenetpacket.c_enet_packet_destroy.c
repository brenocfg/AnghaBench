#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; struct TYPE_5__* data; int /*<<< orphan*/  (* freeCallback ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ ENetPacket ;

/* Variables and functions */
 int ENET_PACKET_FLAG_NO_ALLOCATE ; 
 int /*<<< orphan*/  enet_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
enet_packet_destroy (ENetPacket * packet)
{
    if (packet -> freeCallback != NULL)
      (* packet -> freeCallback) (packet);
    if (! (packet -> flags & ENET_PACKET_FLAG_NO_ALLOCATE) &&
        packet -> data != NULL)
      enet_free (packet -> data);
    enet_free (packet);
}