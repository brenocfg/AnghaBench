#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {TYPE_1__* priv; TYPE_2__** inputs; } ;
struct TYPE_7__ {int format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  hwframes_ref; } ;
typedef  TYPE_1__ HWDownloadContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_HWFRAME_TRANSFER_DIRECTION_FROM ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int av_hwframe_transfer_get_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwdownload_config_output(AVFilterLink *outlink)
{
    AVFilterContext *avctx = outlink->src;
    AVFilterLink *inlink   = avctx->inputs[0];
    HWDownloadContext *ctx = avctx->priv;
    enum AVPixelFormat *formats;
    int err, i, found;

    if (!ctx->hwframes_ref)
        return AVERROR(EINVAL);

    err = av_hwframe_transfer_get_formats(ctx->hwframes_ref,
                                          AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                          &formats, 0);
    if (err < 0)
        return err;

    found = 0;
    for (i = 0; formats[i] != AV_PIX_FMT_NONE; i++) {
        if (formats[i] == outlink->format) {
            found = 1;
            break;
        }
    }
    av_freep(&formats);

    if (!found) {
        av_log(ctx, AV_LOG_ERROR, "Invalid output format %s for hwframe "
               "download.\n", av_get_pix_fmt_name(outlink->format));
        return AVERROR(EINVAL);
    }

    outlink->w = inlink->w;
    outlink->h = inlink->h;

    return 0;
}