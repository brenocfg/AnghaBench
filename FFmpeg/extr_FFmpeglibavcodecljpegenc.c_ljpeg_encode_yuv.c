#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int* hsample; int* vsample; int /*<<< orphan*/  pred; } ;
struct TYPE_10__ {int const buf_end; int const buf; } ;
typedef  TYPE_1__ PutBitContext ;
typedef  TYPE_2__ LJpegEncContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ljpeg_encode_yuv_mb (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int) ; 
 int put_bits_count (TYPE_1__*) ; 

__attribute__((used)) static int ljpeg_encode_yuv(AVCodecContext *avctx, PutBitContext *pb,
                            const AVFrame *frame)
{
    LJpegEncContext *s  = avctx->priv_data;
    const int mb_width  = (avctx->width  + s->hsample[0] - 1) / s->hsample[0];
    const int mb_height = (avctx->height + s->vsample[0] - 1) / s->vsample[0];
    int mb_x, mb_y;

#if FF_API_PRIVATE_OPT
FF_DISABLE_DEPRECATION_WARNINGS
    if (avctx->prediction_method)
        s->pred = avctx->prediction_method + 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    for (mb_y = 0; mb_y < mb_height; mb_y++) {
        if (pb->buf_end - pb->buf - (put_bits_count(pb) >> 3) <
            mb_width * 4 * 3 * s->hsample[0] * s->vsample[0]) {
            av_log(avctx, AV_LOG_ERROR, "encoded frame too large\n");
            return -1;
        }

        for (mb_x = 0; mb_x < mb_width; mb_x++)
            ljpeg_encode_yuv_mb(s, pb, frame, s->pred, mb_x, mb_y);
    }

    return 0;
}