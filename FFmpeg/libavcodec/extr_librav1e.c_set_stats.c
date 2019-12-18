#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pass_size; scalar_t__ pass_pos; scalar_t__ pass_data; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ librav1eContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int rav1e_twopass_in (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int set_stats(AVCodecContext *avctx)
{
    librav1eContext *ctx = avctx->priv_data;
    int ret = 1;

    while (ret > 0 && ctx->pass_size - ctx->pass_pos > 0) {
        ret = rav1e_twopass_in(ctx->ctx, ctx->pass_data + ctx->pass_pos, ctx->pass_size);
        if (ret < 0)
            return AVERROR_EXTERNAL;
        ctx->pass_pos += ret;
    }

    return 0;
}