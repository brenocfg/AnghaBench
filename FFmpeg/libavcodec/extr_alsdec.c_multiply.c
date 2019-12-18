#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int int32_t ;
struct TYPE_7__ {int sign; scalar_t__ exp; scalar_t__ mant; } ;
typedef  TYPE_1__ SoftFloat_IEEE754 ;

/* Variables and functions */
 TYPE_1__ FLOAT_0 ; 
 TYPE_1__ av_bits2sf_ieee754 (unsigned int) ; 
 scalar_t__ av_clip (scalar_t__,int,int) ; 

__attribute__((used)) static SoftFloat_IEEE754 multiply(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    uint64_t mantissa_temp;
    uint64_t mask_64;
    int cutoff_bit_count;
    unsigned char last_2_bits;
    unsigned int mantissa;
    int32_t sign;
    uint32_t return_val = 0;
    int bit_count       = 48;

    sign = a.sign ^ b.sign;

    // Multiply mantissa bits in a 64-bit register
    mantissa_temp = (uint64_t)a.mant * (uint64_t)b.mant;
    mask_64       = (uint64_t)0x1 << 47;

    if (!mantissa_temp)
        return FLOAT_0;

    // Count the valid bit count
    while (!(mantissa_temp & mask_64) && mask_64) {
        bit_count--;
        mask_64 >>= 1;
    }

    // Round off
    cutoff_bit_count = bit_count - 24;
    if (cutoff_bit_count > 0) {
        last_2_bits = (unsigned char)(((unsigned int)mantissa_temp >> (cutoff_bit_count - 1)) & 0x3 );
        if ((last_2_bits == 0x3) || ((last_2_bits == 0x1) && ((unsigned int)mantissa_temp & ((0x1UL << (cutoff_bit_count - 1)) - 1)))) {
            // Need to round up
            mantissa_temp += (uint64_t)0x1 << cutoff_bit_count;
        }
    }

    if (cutoff_bit_count >= 0) {
        mantissa = (unsigned int)(mantissa_temp >> cutoff_bit_count);
    } else {
        mantissa = (unsigned int)(mantissa_temp <<-cutoff_bit_count);
    }

    // Need one more shift?
    if (mantissa & 0x01000000ul) {
        bit_count++;
        mantissa >>= 1;
    }

    if (!sign) {
        return_val = 0x80000000U;
    }

    return_val |= ((unsigned)av_clip(a.exp + b.exp + bit_count - 47, -126, 127) << 23) & 0x7F800000;
    return_val |= mantissa;
    return av_bits2sf_ieee754(return_val);
}