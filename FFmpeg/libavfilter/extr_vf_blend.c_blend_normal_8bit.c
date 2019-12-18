#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  double uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_3__ {double opacity; } ;
typedef  TYPE_1__ FilterParams ;

/* Variables and functions */

__attribute__((used)) static void blend_normal_8bit(const uint8_t *top, ptrdiff_t top_linesize,
                              const uint8_t *bottom, ptrdiff_t bottom_linesize,
                              uint8_t *dst, ptrdiff_t dst_linesize,
                              ptrdiff_t width, ptrdiff_t height,
                              FilterParams *param, double *values, int starty)
{
    const double opacity = param->opacity;
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            dst[j] = top[j] * opacity + bottom[j] * (1. - opacity);
        }
        dst    += dst_linesize;
        top    += top_linesize;
        bottom += bottom_linesize;
    }
}