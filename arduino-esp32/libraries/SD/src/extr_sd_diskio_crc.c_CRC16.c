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

/* Variables and functions */
 unsigned short* m_CRC16Table ; 

unsigned short CRC16(const char* data, int length)
{
    unsigned short crc = 0;
    for (int i = 0; i < length; i++) {
        crc = (crc << 8) ^ m_CRC16Table[((crc >> 8) ^ data[i]) & 0x00FF];
    }
    return crc;
}