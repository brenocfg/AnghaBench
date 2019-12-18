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
struct TYPE_4__ {int /*<<< orphan*/ * op_data; int /*<<< orphan*/  ctex_data; int /*<<< orphan*/  tex_data; } ;
typedef  TYPE_1__ DXVContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dxv_close(AVCodecContext *avctx)
{
    DXVContext *ctx = avctx->priv_data;

    av_freep(&ctx->tex_data);
    av_freep(&ctx->ctex_data);
    av_freep(&ctx->op_data[0]);
    av_freep(&ctx->op_data[1]);
    av_freep(&ctx->op_data[2]);
    av_freep(&ctx->op_data[3]);

    return 0;
}