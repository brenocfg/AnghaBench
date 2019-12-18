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
typedef  unsigned int uint16_t ;
typedef  int ptrdiff_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_3__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 unsigned int const av_clip_uintp2_c (scalar_t__,int) ; 

__attribute__((used)) static void postprocess_chroma(AVFrame *frame, int w, int h, int depth)
{
    uint16_t *dstu = (uint16_t *)frame->data[1];
    uint16_t *dstv = (uint16_t *)frame->data[2];
    int16_t *srcu  = (int16_t *)frame->data[1];
    int16_t *srcv  = (int16_t *)frame->data[2];
    ptrdiff_t strideu = frame->linesize[1] / 2;
    ptrdiff_t stridev = frame->linesize[2] / 2;
    const unsigned add = 1 << (depth - 1);
    const unsigned shift = 16 - depth;
    int i, j;

    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            dstu[i] = av_clip_uintp2_c(add + srcu[i], depth) << shift;
            dstv[i] = av_clip_uintp2_c(add + srcv[i], depth) << shift;
        }
        dstu += strideu;
        dstv += stridev;
        srcu += strideu;
        srcv += stridev;
    }
}