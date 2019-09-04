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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_8__ {TYPE_1__* avctx; } ;
typedef  TYPE_2__ TgqContext ;
struct TYPE_9__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  tgq_dconly (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void tgq_idct_put_mb_dconly(TgqContext *s, AVFrame *frame,
                                   int mb_x, int mb_y, const int8_t *dc)
{
    ptrdiff_t linesize = frame->linesize[0];
    uint8_t *dest_y  = frame->data[0] + (mb_y * 16 * linesize)             + mb_x * 16;
    uint8_t *dest_cb = frame->data[1] + (mb_y * 8  * frame->linesize[1]) + mb_x * 8;
    uint8_t *dest_cr = frame->data[2] + (mb_y * 8  * frame->linesize[2]) + mb_x * 8;
    tgq_dconly(s, dest_y,                    linesize, dc[0]);
    tgq_dconly(s, dest_y                + 8, linesize, dc[1]);
    tgq_dconly(s, dest_y + 8 * linesize,     linesize, dc[2]);
    tgq_dconly(s, dest_y + 8 * linesize + 8, linesize, dc[3]);
    if (!(s->avctx->flags & AV_CODEC_FLAG_GRAY)) {
        tgq_dconly(s, dest_cb, frame->linesize[1], dc[4]);
        tgq_dconly(s, dest_cr, frame->linesize[2], dc[5]);
    }
}