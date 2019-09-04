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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int mb_y; int mb_x; } ;
typedef  TYPE_1__ TqiContext ;
struct TYPE_8__ {int flags; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 int /*<<< orphan*/  ff_ea_idct_put_c (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void tqi_idct_put(AVCodecContext *avctx, AVFrame *frame,
                                int16_t (*block)[64])
{
    TqiContext *t = avctx->priv_data;
    ptrdiff_t linesize = frame->linesize[0];
    uint8_t *dest_y  = frame->data[0] + t->mb_y * 16 * linesize           + t->mb_x * 16;
    uint8_t *dest_cb = frame->data[1] + t->mb_y *  8 * frame->linesize[1] + t->mb_x *  8;
    uint8_t *dest_cr = frame->data[2] + t->mb_y *  8 * frame->linesize[2] + t->mb_x *  8;

    ff_ea_idct_put_c(dest_y                 , linesize, block[0]);
    ff_ea_idct_put_c(dest_y              + 8, linesize, block[1]);
    ff_ea_idct_put_c(dest_y + 8*linesize    , linesize, block[2]);
    ff_ea_idct_put_c(dest_y + 8*linesize + 8, linesize, block[3]);

    if (!(avctx->flags & AV_CODEC_FLAG_GRAY)) {
        ff_ea_idct_put_c(dest_cb, frame->linesize[1], block[4]);
        ff_ea_idct_put_c(dest_cr, frame->linesize[2], block[5]);
    }
}