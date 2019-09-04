#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* fdct ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_pixels ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_12__ {TYPE_3__ fdsp; TYPE_2__ pdsp; TYPE_1__* avctx; int /*<<< orphan*/  block; } ;
struct TYPE_11__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ ASV1Context ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/ * block ; 
 int /*<<< orphan*/ * int16_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dct_get(ASV1Context *a, const AVFrame *frame,
                           int mb_x, int mb_y)
{
    int16_t (*block)[64] = a->block;
    int linesize = frame->linesize[0];
    int i;

    uint8_t *ptr_y  = frame->data[0] + (mb_y * 16 * linesize)           + mb_x * 16;
    uint8_t *ptr_cb = frame->data[1] + (mb_y *  8 * frame->linesize[1]) + mb_x *  8;
    uint8_t *ptr_cr = frame->data[2] + (mb_y *  8 * frame->linesize[2]) + mb_x *  8;

    a->pdsp.get_pixels(block[0], ptr_y,                    linesize);
    a->pdsp.get_pixels(block[1], ptr_y + 8,                linesize);
    a->pdsp.get_pixels(block[2], ptr_y + 8 * linesize,     linesize);
    a->pdsp.get_pixels(block[3], ptr_y + 8 * linesize + 8, linesize);
    for (i = 0; i < 4; i++)
        a->fdsp.fdct(block[i]);

    if (!(a->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        a->pdsp.get_pixels(block[4], ptr_cb, frame->linesize[1]);
        a->pdsp.get_pixels(block[5], ptr_cr, frame->linesize[2]);
        for (i = 4; i < 6; i++)
            a->fdsp.fdct(block[i]);
    }
}