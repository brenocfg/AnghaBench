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
typedef  int uint8_t ;

/* Variables and functions */
 int FFABS (int) ; 
 int av_clip (int,int,int) ; 
 int* ff_h263_loop_filter_strength ; 

__attribute__((used)) static void h263_h_loop_filter_c(uint8_t *src, int stride, int qscale)
{
    int y;
    const int strength = ff_h263_loop_filter_strength[qscale];

    for (y = 0; y < 8; y++) {
        int d1, d2, ad1;
        int p0 = src[y * stride - 2];
        int p1 = src[y * stride - 1];
        int p2 = src[y * stride + 0];
        int p3 = src[y * stride + 1];
        int d  = (p0 - p3 + 4 * (p2 - p1)) / 8;

        if (d < -2 * strength)
            d1 = 0;
        else if (d < -strength)
            d1 = -2 * strength - d;
        else if (d < strength)
            d1 = d;
        else if (d < 2 * strength)
            d1 = 2 * strength - d;
        else
            d1 = 0;

        p1 += d1;
        p2 -= d1;
        if (p1 & 256)
            p1 = ~(p1 >> 31);
        if (p2 & 256)
            p2 = ~(p2 >> 31);

        src[y * stride - 1] = p1;
        src[y * stride + 0] = p2;

        ad1 = FFABS(d1) >> 1;

        d2 = av_clip((p0 - p3) / 4, -ad1, ad1);

        src[y * stride - 2] = p0 - d2;
        src[y * stride + 1] = p3 + d2;
    }
}