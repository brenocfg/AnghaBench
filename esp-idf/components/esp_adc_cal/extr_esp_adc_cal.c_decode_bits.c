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

/* Variables and functions */

__attribute__((used)) static inline int decode_bits(uint32_t bits, uint32_t mask, bool is_twos_compl)
{
    int ret;
    if (bits & (~(mask >> 1) & mask)) {      //Check sign bit (MSB of mask)
        //Negative
        if (is_twos_compl) {
            ret = -(((~bits) + 1) & (mask >> 1));   //2's complement
        } else {
            ret = -(bits & (mask >> 1));    //Sign-magnitude
        }
    } else {
        //Positive
        ret = bits & (mask >> 1);
    }
    return ret;
}