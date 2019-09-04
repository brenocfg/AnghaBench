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

void pack12bit(uint8_t *buf, int index, uint16_t inVal) {
    int addr = (index * 12) / 8;
    int offset = 4-(index * 12) % 8;
    // compute the mask and value shifted into the correct location in the bit array
    uint16_t value = (inVal & 0xFFF) << offset;
    uint16_t mask = ~(0x0FFF << offset);

    // zero out the bits we are working on
    buf[addr]   &= mask >> 8;
    buf[addr+1] &= mask & 0xFF;
    // copy the value into the destination
    buf[addr]   |= value >> 8;
    buf[addr+1] |= value & 0xFF;
}