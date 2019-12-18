#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * op_size; int /*<<< orphan*/ * op_data; int /*<<< orphan*/  ctex_size; int /*<<< orphan*/  ctex_data; int /*<<< orphan*/  tex_size; int /*<<< orphan*/  tex_data; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ DXVContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int dxv_decompress_cocg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dxv_decompress_yo (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxv_decompress_ycg6(AVCodecContext *avctx)
{
    DXVContext *ctx = avctx->priv_data;
    GetByteContext *gb = &ctx->gbc;
    int ret;

    ret = dxv_decompress_yo(ctx, gb, ctx->tex_data, ctx->tex_size,
                            ctx->op_data[0], ctx->op_size[0]);
    if (ret < 0)
        return ret;

    return dxv_decompress_cocg(ctx, gb, ctx->ctex_data, ctx->ctex_size,
                               ctx->op_data[1], ctx->op_data[2],
                               ctx->op_size[1], ctx->op_size[2]);
}