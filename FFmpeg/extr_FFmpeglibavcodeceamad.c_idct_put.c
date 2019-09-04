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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {TYPE_1__* avctx; } ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ MadContext ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  ff_ea_idct_put_c (scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void idct_put(MadContext *t, AVFrame *frame, int16_t *block,
                            int mb_x, int mb_y, int j)
{
    if (j < 4) {
        ff_ea_idct_put_c(
            frame->data[0] + (mb_y*16 + ((j&2)<<2))*frame->linesize[0] + mb_x*16 + ((j&1)<<3),
            frame->linesize[0], block);
    } else if (!(t->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        int index = j - 3;
        ff_ea_idct_put_c(
            frame->data[index] + (mb_y*8)*frame->linesize[index] + mb_x*8,
            frame->linesize[index], block);
    }
}