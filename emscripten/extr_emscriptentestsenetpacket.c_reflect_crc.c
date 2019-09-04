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
typedef  int enet_uint32 ;

/* Variables and functions */

__attribute__((used)) static enet_uint32 
reflect_crc (int val, int bits)
{
    int result = 0, bit;

    for (bit = 0; bit < bits; bit ++)
    {
        if(val & 1) result |= 1 << (bits - 1 - bit); 
        val >>= 1;
    }

    return result;
}