#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int plane; int step; } ;
struct TYPE_7__ {int crop_top; int* linesize; int crop_left; scalar_t__* data; } ;
struct TYPE_6__ {int log2_chroma_w; int log2_chroma_h; int flags; int nb_components; TYPE_3__* comp; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVComponentDescriptor ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int FF_PSEUDOPAL ; 

__attribute__((used)) static int calc_cropping_offsets(size_t offsets[4], const AVFrame *frame,
                                 const AVPixFmtDescriptor *desc)
{
    int i, j;

    for (i = 0; frame->data[i]; i++) {
        const AVComponentDescriptor *comp = NULL;
        int shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        int shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        if (desc->flags & (AV_PIX_FMT_FLAG_PAL | FF_PSEUDOPAL) && i == 1) {
            offsets[i] = 0;
            break;
        }

        /* find any component descriptor for this plane */
        for (j = 0; j < desc->nb_components; j++) {
            if (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                break;
            }
        }
        if (!comp)
            return AVERROR_BUG;

        offsets[i] = (frame->crop_top  >> shift_y) * frame->linesize[i] +
                     (frame->crop_left >> shift_x) * comp->step;
    }

    return 0;
}