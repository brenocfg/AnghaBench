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
typedef  unsigned int uint16_t ;

/* Variables and functions */
 int MUL16 (int,int) ; 
 int MULH (int,unsigned int) ; 
 scalar_t__ UMULH (unsigned int,unsigned int const) ; 

__attribute__((used)) static int pRNG(int frame_cntr, int block_num, int block_size)
{
    /* array to simplify the calculation of z:
     * y = (x % 9) * 5 + 6;
     * z = (49995 * x) / y;
     * Since y only has 9 values, we can remove the division by using a
     * LUT and using FASTDIV-style divisions. For each of the 9 values
     * of y, we can rewrite z as:
     * z = x * (49995 / y) + x * ((49995 % y) / y)
     * In this table, each col represents one possible value of y, the
     * first number is 49995 / y, and the second is the FASTDIV variant
     * of 49995 % y / y. */
    static const unsigned int div_tbl[9][2] = {
        { 8332,  3 * 715827883U }, // y =  6
        { 4545,  0 * 390451573U }, // y = 11
        { 3124, 11 * 268435456U }, // y = 16
        { 2380, 15 * 204522253U }, // y = 21
        { 1922, 23 * 165191050U }, // y = 26
        { 1612, 23 * 138547333U }, // y = 31
        { 1388, 27 * 119304648U }, // y = 36
        { 1219, 16 * 104755300U }, // y = 41
        { 1086, 39 *  93368855U }  // y = 46
    };
    unsigned int z, y, x = MUL16(block_num, 1877) + frame_cntr;
    if (x >= 0xFFFF) x -= 0xFFFF;   // max value of x is 8*1877+0xFFFE=0x13AA6,
                                    // so this is effectively a modulo (%)
    y = x - 9 * MULH(477218589, x); // x % 9
    z = (uint16_t) (x * div_tbl[y][0] + UMULH(x, div_tbl[y][1]));
                                    // z = x * 49995 / (y * 5 + 6)
    return z % (1000 - block_size);
}