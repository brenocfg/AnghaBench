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
 int** sipr_swaps ; 

void ff_rm_reorder_sipr_data(uint8_t *buf, int sub_packet_h, int framesize)
{
    int n, bs = sub_packet_h * framesize * 2 / 96; // nibbles per subpacket

    for (n = 0; n < 38; n++) {
        int j;
        int i = bs * sipr_swaps[n][0];
        int o = bs * sipr_swaps[n][1];

        /* swap 4bit-nibbles of block 'i' with 'o' */
        for (j = 0; j < bs; j++, i++, o++) {
            int x = (buf[i >> 1] >> (4 * (i & 1))) & 0xF,
                y = (buf[o >> 1] >> (4 * (o & 1))) & 0xF;

            buf[o >> 1] = (x << (4 * (o & 1))) |
                (buf[o >> 1] & (0xF << (4 * !(o & 1))));
            buf[i >> 1] = (y << (4 * (i & 1))) |
                (buf[i >> 1] & (0xF << (4 * !(i & 1))));
        }
    }
}