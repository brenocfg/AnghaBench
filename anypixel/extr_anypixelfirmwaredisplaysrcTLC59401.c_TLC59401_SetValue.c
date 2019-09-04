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
 int* txpacket ; 

void TLC59401_SetValue(int index, int value) {
    int addr = (index * 3) / 2;
    if(index & 1) {
        // odd so first 4 msb in first byte, 8 bits in second
        txpacket[addr] &= 0xF0;   // erase the low 4 bits we are writing to
        txpacket[addr] |= ((value >> 8) & 0x0F);  // store the 4 msb of the input in the low 4 bits of the first packet byte
        txpacket[addr+1] = value & 0xFF;
    } else {
        txpacket[addr] = (value >> 4) & 0xFF;
        txpacket[addr+1] &= 0x0F; // erase the high 4 bits we are writing to
        txpacket[addr+1] |= (value << 4) & 0xF0;
    }
}