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
typedef  int u8 ;
typedef  size_t u32 ;

/* Variables and functions */

u32
CardComputeCrc(u8 * Buffer, u32 Length)
{
    u32 Crc, Carry;
    u32  i, j;
    u8 CurByte;

    Crc = 0xffffffff;

    for (i = 0; i < Length; i++) {

        CurByte = Buffer[i];

        for (j = 0; j < 8; j++) {

            Carry     = ((Crc & 0x80000000) ? 1 : 0) ^ (CurByte & 0x01);
            Crc     <<= 1;
            CurByte >>= 1;

            if (Carry) {
                Crc =(Crc ^ 0x04c11db6) | Carry;
            }
        }
    }

    return Crc;
}