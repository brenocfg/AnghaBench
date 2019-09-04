#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int enet_uint32 ;

/* Variables and functions */
 int* crcTable ; 
 int initializedCRC32 ; 
 int reflect_crc (int,int) ; 

__attribute__((used)) static void 
initialize_crc32 ()
{
    int byte;

    for (byte = 0; byte < 256; ++ byte)
    {
        enet_uint32 crc = reflect_crc (byte, 8) << 24;
        int offset;

        for(offset = 0; offset < 8; ++ offset)
        {
            if (crc & 0x80000000)
                crc = (crc << 1) ^ 0x04c11db7;
            else
                crc <<= 1;
        }

        crcTable [byte] = reflect_crc (crc, 32);
    }

    initializedCRC32 = 1;
}