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
typedef  int const uint32_t ;

/* Variables and functions */
 int const BARREL_SHIFT (int const,int const) ; 

__attribute__((used)) static uint32_t
buzhash_update(uint32_t sum, unsigned char remove, unsigned char add, size_t len, const uint32_t *h)
{
    uint32_t lenmod = len & 0x1f;  /* Note: replace by constant to get small speedup */
    return BARREL_SHIFT(sum, 1) ^ BARREL_SHIFT(h[remove], lenmod) ^ h[add];
}