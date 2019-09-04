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
struct TYPE_4__ {scalar_t__ tex_size; int /*<<< orphan*/  tex_data; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ DXVContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dxv_decompress_raw(AVCodecContext *avctx)
{
    DXVContext *ctx = avctx->priv_data;
    GetByteContext *gbc = &ctx->gbc;

    if (bytestream2_get_bytes_left(gbc) < ctx->tex_size)
        return AVERROR_INVALIDDATA;

    bytestream2_get_buffer(gbc, ctx->tex_data, ctx->tex_size);
    return 0;
}