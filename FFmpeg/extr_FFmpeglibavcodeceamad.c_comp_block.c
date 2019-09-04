#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {TYPE_2__* last_frame; TYPE_1__* avctx; } ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int height; int flags; } ;
typedef  TYPE_3__ MadContext ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  comp (scalar_t__,int,scalar_t__,int,int) ; 

__attribute__((used)) static inline void comp_block(MadContext *t, AVFrame *frame,
                              int mb_x, int mb_y,
                              int j, int mv_x, int mv_y, int add)
{
    if (j < 4) {
        unsigned offset = (mb_y*16 + ((j&2)<<2) + mv_y)*t->last_frame->linesize[0] + mb_x*16 + ((j&1)<<3) + mv_x;
        if (offset >= (t->avctx->height - 7) * t->last_frame->linesize[0] - 7)
            return;
        comp(frame->data[0] + (mb_y*16 + ((j&2)<<2))*frame->linesize[0] + mb_x*16 + ((j&1)<<3),
             frame->linesize[0],
             t->last_frame->data[0] + offset,
             t->last_frame->linesize[0], add);
    } else if (!(t->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        int index = j - 3;
        unsigned offset = (mb_y * 8 + (mv_y/2))*t->last_frame->linesize[index] + mb_x * 8 + (mv_x/2);
        if (offset >= (t->avctx->height/2 - 7) * t->last_frame->linesize[index] - 7)
            return;
        comp(frame->data[index] + (mb_y*8)*frame->linesize[index] + mb_x * 8,
             frame->linesize[index],
             t->last_frame->data[index] + offset,
             t->last_frame->linesize[index], add);
    }
}