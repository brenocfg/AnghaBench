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
 char* m_CRC7Table ; 

char CRC7(const char* data, int length)
{
    char crc = 0;
    for (int i = 0; i < length; i++) {
        crc = m_CRC7Table[(crc << 1) ^ data[i]];
    }
    return crc;
}