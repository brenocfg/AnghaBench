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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  hevc_avctx; int /*<<< orphan*/  h264_avctx; } ;
typedef  TYPE_1__ IMM5Context ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imm5_flush(AVCodecContext *avctx)
{
    IMM5Context *ctx = avctx->priv_data;

    avcodec_flush_buffers(ctx->h264_avctx);
    avcodec_flush_buffers(ctx->hevc_avctx);
}