#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VLC ;
struct TYPE_11__ {int height; } ;
struct TYPE_10__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {TYPE_3__* avctx; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ CLLCContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_argb_line (TYPE_1__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_code_table (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_argb_frame(CLLCContext *ctx, GetBitContext *gb, AVFrame *pic)
{
    AVCodecContext *avctx = ctx->avctx;
    uint8_t *dst;
    int pred[4];
    int ret;
    int i, j;
    VLC vlc[4];

    pred[0] = 0;
    pred[1] = 0x80;
    pred[2] = 0x80;
    pred[3] = 0x80;

    dst = pic->data[0];

    skip_bits(gb, 16);

    /* Read in code table for each plane */
    for (i = 0; i < 4; i++) {
        ret = read_code_table(ctx, gb, &vlc[i]);
        if (ret < 0) {
            for (j = 0; j <= i; j++)
                ff_free_vlc(&vlc[j]);

            av_log(ctx->avctx, AV_LOG_ERROR,
                   "Could not read code table %d.\n", i);
            return ret;
        }
    }

    /* Read in and restore every line */
    for (i = 0; i < avctx->height; i++) {
        read_argb_line(ctx, gb, pred, vlc, dst);

        dst += pic->linesize[0];
    }

    for (i = 0; i < 4; i++)
        ff_free_vlc(&vlc[i]);

    return 0;
}