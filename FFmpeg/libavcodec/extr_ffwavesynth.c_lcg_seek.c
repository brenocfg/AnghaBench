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
 int LCG_A ; 
 int LCG_C ; 

__attribute__((used)) static void lcg_seek(uint32_t *s, uint32_t dt)
{
    uint32_t a, c, t = *s;

    a = LCG_A;
    c = LCG_C;
    while (dt) {
        if (dt & 1)
            t = a * t + c;
        c *= a + 1; /* coefficients for a double step */
        a *= a;
        dt >>= 1;
    }
    *s = t;
}