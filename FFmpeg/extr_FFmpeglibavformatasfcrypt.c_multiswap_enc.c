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
 int multiswap_step (int const*,int) ; 

__attribute__((used)) static uint64_t multiswap_enc(const uint32_t keys[12],
                              uint64_t key, uint64_t data)
{
    uint32_t a = data;
    uint32_t b = data >> 32;
    uint32_t c;
    uint32_t tmp;
    a  += key;
    tmp = multiswap_step(keys, a);
    b  += tmp;
    c   = (key >> 32) + tmp;
    tmp = multiswap_step(keys + 6, b);
    c  += tmp;
    return ((uint64_t)c << 32) | tmp;
}