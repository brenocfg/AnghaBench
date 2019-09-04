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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* idct_put ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_2__ idsp; TYPE_1__* avctx; int /*<<< orphan*/  block; } ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ MDECContext ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/ * block ; 
 int /*<<< orphan*/ * int16_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void idct_put(MDECContext *a, AVFrame *frame, int mb_x, int mb_y)
{
    int16_t (*block)[64] = a->block;
    int linesize = frame->linesize[0];

    uint8_t *dest_y  = frame->data[0] + (mb_y * 16* linesize              ) + mb_x * 16;
    uint8_t *dest_cb = frame->data[1] + (mb_y * 8 * frame->linesize[1]) + mb_x * 8;
    uint8_t *dest_cr = frame->data[2] + (mb_y * 8 * frame->linesize[2]) + mb_x * 8;

    a->idsp.idct_put(dest_y,                    linesize, block[0]);
    a->idsp.idct_put(dest_y + 8,                linesize, block[1]);
    a->idsp.idct_put(dest_y + 8 * linesize,     linesize, block[2]);
    a->idsp.idct_put(dest_y + 8 * linesize + 8, linesize, block[3]);

    if (!(a->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        a->idsp.idct_put(dest_cb, frame->linesize[1], block[4]);
        a->idsp.idct_put(dest_cr, frame->linesize[2], block[5]);
    }
}