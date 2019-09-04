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
typedef  int uint16_t ;

/* Variables and functions */

uint8_t unpack6bit(uint8_t *buf, int index) {
    uint16_t retval = 0;
    int addr = (index * 6) / 8;
    int offset = 10-(index * 6) % 8;

    // compute the mask shifted into the correct location in the bit array
    uint16_t mask = (0x003F << offset);

    // extract the relevant bytes
    retval = buf[addr] << 8 | buf[addr+1];
    // mask of the unwanted bits
    retval &= mask;
    // shift into the LSBs
    retval >>= offset;
    return retval;
}