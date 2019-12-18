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
typedef  int uint16_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static inline void wdec14(uint16_t l, uint16_t h, uint16_t *a, uint16_t *b)
{
    int16_t ls = l;
    int16_t hs = h;
    int hi     = hs;
    int ai     = ls + (hi & 1) + (hi >> 1);
    int16_t as = ai;
    int16_t bs = ai - hi;

    *a = as;
    *b = bs;
}