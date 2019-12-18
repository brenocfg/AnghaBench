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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int INT_MAX ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_run_2bit(GetBitContext *gb, int *color)
{
    unsigned int v, t;

    v = 0;
    for (t = 1; v < t && t <= 0x40; t <<= 2)
        v = (v << 4) | get_bits(gb, 4);
    *color = v & 3;
    if (v < 4) { /* Code for fill rest of line */
        return INT_MAX;
    }
    return v >> 2;
}