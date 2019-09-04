#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  enet_uint8 ;
typedef  int enet_uint32 ;
struct TYPE_4__ {int flags; size_t dataLength; int /*<<< orphan*/ * freeCallback; scalar_t__ referenceCount; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ENetPacket ;

/* Variables and functions */
 int ENET_PACKET_FLAG_NO_ALLOCATE ; 
 int /*<<< orphan*/  enet_free (TYPE_1__*) ; 
 scalar_t__ enet_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

ENetPacket *
enet_packet_create (const void * data, size_t dataLength, enet_uint32 flags)
{
    ENetPacket * packet = (ENetPacket *) enet_malloc (sizeof (ENetPacket));
    if (packet == NULL)
      return NULL;

    if (flags & ENET_PACKET_FLAG_NO_ALLOCATE)
      packet -> data = (enet_uint8 *) data;
    else
    if (dataLength <= 0)
      packet -> data = NULL;
    else
    {
       packet -> data = (enet_uint8 *) enet_malloc (dataLength);
       if (packet -> data == NULL)
       {
          enet_free (packet);
          return NULL;
       }

       if (data != NULL)
         memcpy (packet -> data, data, dataLength);
    }

    packet -> referenceCount = 0;
    packet -> flags = flags;
    packet -> dataLength = dataLength;
    packet -> freeCallback = NULL;

    return packet;
}