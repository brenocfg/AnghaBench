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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 long long av_log2 (int) ; 

__attribute__((used)) static uint32_t softfloat_mul(uint32_t x, uint64_t mantissa)
{
    uint64_t l = x * (mantissa & 0xffffffff);
    uint64_t h = x * (mantissa >> 32);
    h += l >> 32;
    l &= 0xffffffff;
    l += 1LL << av_log2(h >> 21);
    h += l >> 32;
    return h >> 20;
}