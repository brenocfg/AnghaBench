#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* draw_horiz_band ) (TYPE_3__*,TYPE_2__*,int*,int,int,int) ;} ;
struct TYPE_8__ {int* linesize; } ;
struct TYPE_7__ {int last_slice_end; int bitstream_bpp; TYPE_3__* avctx; } ;
typedef  TYPE_1__ HYuvContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_NUM_DATA_POINTERS ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int*,int,int,int) ; 

__attribute__((used)) static void draw_slice(HYuvContext *s, AVFrame *frame, int y)
{
    int h, cy, i;
    int offset[AV_NUM_DATA_POINTERS];

    if (!s->avctx->draw_horiz_band)
        return;

    h  = y - s->last_slice_end;
    y -= h;

    if (s->bitstream_bpp == 12)
        cy = y >> 1;
    else
        cy = y;

    offset[0] = frame->linesize[0] * y;
    offset[1] = frame->linesize[1] * cy;
    offset[2] = frame->linesize[2] * cy;
    for (i = 3; i < AV_NUM_DATA_POINTERS; i++)
        offset[i] = 0;
    emms_c();

    s->avctx->draw_horiz_band(s->avctx, frame, offset, y, 3, h);

    s->last_slice_end = y + h;
}