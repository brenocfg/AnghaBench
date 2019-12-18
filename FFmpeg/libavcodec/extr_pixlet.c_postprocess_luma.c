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
typedef  int uint16_t ;
typedef  int ptrdiff_t ;
typedef  int int64_t ;
typedef  int int16_t ;
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static void postprocess_luma(AVFrame *frame, int w, int h, int depth)
{
    uint16_t *dsty = (uint16_t *)frame->data[0];
    int16_t *srcy  = (int16_t *)frame->data[0];
    ptrdiff_t stridey = frame->linesize[0] / 2;
    int i, j;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            if (srcy[i] <= 0)
                dsty[i] = 0;
            else if (srcy[i] > ((1 << depth) - 1))
                dsty[i] = 65535;
            else
                dsty[i] = ((int64_t) srcy[i] * srcy[i] * 65535) /
                          ((1 << depth) - 1) / ((1 << depth) - 1);
        }
        dsty += stridey;
        srcy += stridey;
    }
}