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
typedef  int uint8_t ;

/* Variables and functions */
 int av_crc (int*,int,int const*,int) ; 
 int* crc_1D ; 

uint8_t ff_mlp_restart_checksum(const uint8_t *buf, unsigned int bit_size)
{
    int i;
    int num_bytes = (bit_size + 2) / 8;

    int crc = crc_1D[buf[0] & 0x3f];
    crc = av_crc(crc_1D, crc, buf + 1, num_bytes - 2);
    crc ^= buf[num_bytes - 1];

    for (i = 0; i < ((bit_size + 2) & 7); i++) {
        crc <<= 1;
        if (crc & 0x100)
            crc ^= 0x11D;
        crc ^= (buf[num_bytes] >> (7 - i)) & 1;
    }

    return crc;
}