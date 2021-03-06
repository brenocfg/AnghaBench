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
 float av_clipf (float,int,int) ; 

__attribute__((used)) static void filter_fltp(void **d, void **p, const void **s,
                        int nb_samples, int channels,
                        float mult, int clip)
{
    int n, c;

    for (c = 0; c < channels; c++) {
        const float *src = s[c];
        float *dst = d[c];
        float *prv = p[c];

        for (n = 0; n < nb_samples; n++) {
            float current = src[n];

            dst[n] = current + (current - prv[0]) * mult;
            prv[0] = current;
            if (clip) {
                dst[n] = av_clipf(dst[n], -1, 1);
            }
        }
    }
}