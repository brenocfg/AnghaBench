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

/* Variables and functions */
 int A_OFFSET ; 
 int MOD_MASK ; 

__attribute__((used)) static inline void wdec16(uint16_t l, uint16_t h, uint16_t *a, uint16_t *b)
{
    int m  = l;
    int d  = h;
    int bb = (m - (d >> 1)) & MOD_MASK;
    int aa = (d + bb - A_OFFSET) & MOD_MASK;
    *b = bb;
    *a = aa;
}