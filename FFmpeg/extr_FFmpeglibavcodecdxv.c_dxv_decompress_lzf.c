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
struct TYPE_4__ {int /*<<< orphan*/  tex_size; int /*<<< orphan*/  tex_data; int /*<<< orphan*/  gbc; } ;
typedef  TYPE_1__ DXVContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int ff_lzf_uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dxv_decompress_lzf(AVCodecContext *avctx)
{
    DXVContext *ctx = avctx->priv_data;
    return ff_lzf_uncompress(&ctx->gbc, &ctx->tex_data, &ctx->tex_size);
}