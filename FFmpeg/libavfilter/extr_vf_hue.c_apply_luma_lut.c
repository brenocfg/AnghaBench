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
typedef  size_t uint8_t ;
struct TYPE_3__ {size_t* lut_l; } ;
typedef  TYPE_1__ HueContext ;

/* Variables and functions */

__attribute__((used)) static void apply_luma_lut(HueContext *s,
                           uint8_t *ldst, const int dst_linesize,
                           uint8_t *lsrc, const int src_linesize,
                           int w, int h)
{
    int i;

    while (h--) {
        for (i = 0; i < w; i++)
            ldst[i] = s->lut_l[lsrc[i]];

        lsrc += src_linesize;
        ldst += dst_linesize;
    }
}