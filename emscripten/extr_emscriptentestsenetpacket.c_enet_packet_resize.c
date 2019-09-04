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
typedef  int /*<<< orphan*/  enet_uint8 ;
struct TYPE_3__ {size_t dataLength; int flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ENetPacket ;

/* Variables and functions */
 int ENET_PACKET_FLAG_NO_ALLOCATE ; 
 int /*<<< orphan*/  enet_free (int /*<<< orphan*/ *) ; 
 scalar_t__ enet_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

int
enet_packet_resize (ENetPacket * packet, size_t dataLength)
{
    enet_uint8 * newData;
   
    if (dataLength <= packet -> dataLength || (packet -> flags & ENET_PACKET_FLAG_NO_ALLOCATE))
    {
       packet -> dataLength = dataLength;

       return 0;
    }

    newData = (enet_uint8 *) enet_malloc (dataLength);
    if (newData == NULL)
      return -1;

    memcpy (newData, packet -> data, packet -> dataLength);
    enet_free (packet -> data);
    
    packet -> data = newData;
    packet -> dataLength = dataLength;

    return 0;
}