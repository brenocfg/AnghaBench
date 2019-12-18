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

__attribute__((used)) static void sbr_qmf_deint_neg_c(int *v, const int *src)
{
    int i;
    for (i = 0; i < 32; i++) {
        v[     i] = ( src[63 - 2*i    ] + 0x10) >> 5;
        v[63 - i] = (-src[63 - 2*i - 1] + 0x10) >> 5;
    }
}