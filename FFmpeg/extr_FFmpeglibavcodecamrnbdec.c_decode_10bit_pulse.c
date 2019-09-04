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
 int** base_five_table ; 

__attribute__((used)) static void decode_10bit_pulse(int code, int pulse_position[8],
                               int i1, int i2, int i3)
{
    // coded using 7+3 bits with the 3 LSBs being, individually, the LSB of 1 of
    // the 3 pulses and the upper 7 bits being coded in base 5
    const uint8_t *positions = base_five_table[code >> 3];
    pulse_position[i1] = (positions[2] << 1) + ( code       & 1);
    pulse_position[i2] = (positions[1] << 1) + ((code >> 1) & 1);
    pulse_position[i3] = (positions[0] << 1) + ((code >> 2) & 1);
}