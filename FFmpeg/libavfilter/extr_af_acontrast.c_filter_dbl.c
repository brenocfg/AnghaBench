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
 double const M_PI_2 ; 
 float sin (double) ; 

__attribute__((used)) static void filter_dbl(void **d, const void **s,
                       int nb_samples, int channels,
                       float contrast)
{
    const double *src = s[0];
    double *dst = d[0];
    int n, c;

    for (n = 0; n < nb_samples; n++) {
        for (c = 0; c < channels; c++) {
            double d = src[c] * M_PI_2;

            dst[c] = sin(d + contrast * sin(d * 4));
        }

        dst += c;
        src += c;
    }
}