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
 float avpriv_scalarproduct_float_c (float const*,float const*,int) ; 

__attribute__((used)) static void convolve(float *tgt, const float *src, int len, int n)
{
    for (; n >= 0; n--)
        tgt[n] = avpriv_scalarproduct_float_c(src, src - n, len);

}