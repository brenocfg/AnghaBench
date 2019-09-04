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

/* Variables and functions */
 scalar_t__* ff_cbrt_tab_fixed ; 

__attribute__((used)) static void vector_pow43(int *coefs, int len)
{
    int i, coef;

    for (i=0; i<len; i++) {
        coef = coefs[i];
        if (coef < 0)
            coef = -(int)ff_cbrt_tab_fixed[-coef];
        else
            coef = (int)ff_cbrt_tab_fixed[coef];
        coefs[i] = coef;
    }
}