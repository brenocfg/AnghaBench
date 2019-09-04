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
typedef  int int64_t ;

/* Variables and functions */
 int LCG_A ; 
 int LCG_AI ; 
 int LCG_C ; 

__attribute__((used)) static void lcg_seek(uint32_t *s, int64_t dt)
{
    uint32_t a, c, t = *s;

    if (dt >= 0) {
        a = LCG_A;
        c = LCG_C;
    } else { /* coefficients for a step backward */
        a = LCG_AI;
        c = (uint32_t)(LCG_AI * LCG_C);
        dt = -dt;
    }
    while (dt) {
        if (dt & 1)
            t = a * t + c;
        c *= a + 1; /* coefficients for a double step */
        a *= a;
        dt >>= 1;
    }
    *s = t;
}