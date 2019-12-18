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
typedef  int uint32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t get_size_in_bits(uint32_t n)
{
    int16_t bits;

    if (0xFFFF0000 & n) {
        bits = 16;
    } else {
        bits = 0;
    }

    if (0x0000FF00 & (n >> bits)) bits += 8;
    if (0x000000F0 & (n >> bits)) bits += 4;
    if (0x0000000C & (n >> bits)) bits += 2;
    if (0x00000002 & (n >> bits)) bits += 1;
    if (0x00000001 & (n >> bits)) bits += 1;

    return bits;
}