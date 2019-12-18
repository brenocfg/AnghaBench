#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int ff_set_dimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ init_buffers (TYPE_1__*) ; 
 int /*<<< orphan*/  init_sizes (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int old_codec1 (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int old_codec37 (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int old_codec47 (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int process_frame_obj(SANMVideoContext *ctx)
{
    uint16_t codec = bytestream2_get_le16u(&ctx->gb);
    uint16_t left  = bytestream2_get_le16u(&ctx->gb);
    uint16_t top   = bytestream2_get_le16u(&ctx->gb);
    uint16_t w     = bytestream2_get_le16u(&ctx->gb);
    uint16_t h     = bytestream2_get_le16u(&ctx->gb);

    if (!w || !h) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Dimensions are invalid.\n");
        return AVERROR_INVALIDDATA;
    }

    if (ctx->width < left + w || ctx->height < top + h) {
        int ret = ff_set_dimensions(ctx->avctx, FFMAX(left + w, ctx->width),
                                    FFMAX(top + h, ctx->height));
        if (ret < 0)
            return ret;
        init_sizes(ctx, FFMAX(left + w, ctx->width),
                   FFMAX(top + h, ctx->height));
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "Error resizing buffers.\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
    case 37:
        return old_codec37(ctx, top, left, w, h);
    case 47:
        return old_codec47(ctx, top, left, w, h);
    default:
        avpriv_request_sample(ctx->avctx, "Subcodec %d", codec);
        return AVERROR_PATCHWELCOME;
    }
}