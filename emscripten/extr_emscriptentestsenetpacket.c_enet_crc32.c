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
typedef  int enet_uint32 ;
struct TYPE_3__ {size_t dataLength; scalar_t__ data; } ;
typedef  TYPE_1__ ENetBuffer ;

/* Variables and functions */
 int ENET_HOST_TO_NET_32 (int) ; 
 int* crcTable ; 
 int /*<<< orphan*/  initialize_crc32 () ; 
 int /*<<< orphan*/  initializedCRC32 ; 

enet_uint32
enet_crc32 (const ENetBuffer * buffers, size_t bufferCount)
{
    enet_uint32 crc = 0xFFFFFFFF;
    
    if (! initializedCRC32) initialize_crc32 ();

    while (bufferCount -- > 0)
    {
        const enet_uint8 * data = (const enet_uint8 *) buffers -> data,
                         * dataEnd = & data [buffers -> dataLength];

        while (data < dataEnd)
        {
            crc = (crc >> 8) ^ crcTable [(crc & 0xFF) ^ *data++];        
        }

        ++ buffers;
    }

    return ENET_HOST_TO_NET_32 (~ crc);
}