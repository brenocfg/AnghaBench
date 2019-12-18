#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ HQContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int hqa_decode_mb (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int hqa_decode_slice(HQContext *ctx, AVFrame *pic, GetBitContext *gb,
                            int quant, int slice_no, int w, int h)
{
    int i, j, off;
    int ret;

    for (i = 0; i < h; i += 16) {
        off = (slice_no * 16 + i * 3) & 0x70;
        for (j = off; j < w; j += 128) {
            ret = hqa_decode_mb(ctx, pic, quant, gb, j, i);
            if (ret < 0) {
                av_log(ctx->avctx, AV_LOG_ERROR,
                       "Error decoding macroblock at %dx%d.\n", i, j);
                return ret;
            }
        }
    }

    return 0;
}