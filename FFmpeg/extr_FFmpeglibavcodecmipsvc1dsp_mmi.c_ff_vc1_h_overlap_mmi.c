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
 int av_clip_uint8 (int) ; 

void ff_vc1_h_overlap_mmi(uint8_t *src, int stride)
{
    int i;
    int a, b, c, d;
    int d1, d2;
    int rnd = 1;
    for (i = 0; i < 8; i++) {
        a  = src[-2];
        b  = src[-1];
        c  = src[0];
        d  = src[1];
        d1 = (a - d + 3 + rnd) >> 3;
        d2 = (a - d + b - c + 4 - rnd) >> 3;

        src[-2] = a - d1;
        src[-1] = av_clip_uint8(b - d2);
        src[0]  = av_clip_uint8(c + d2);
        src[1]  = d + d1;
        src    += stride;
        rnd     = !rnd;
    }
}