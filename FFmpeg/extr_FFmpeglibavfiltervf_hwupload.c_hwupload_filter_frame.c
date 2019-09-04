#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * priv; TYPE_2__** outputs; } ;
struct TYPE_16__ {scalar_t__ format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* dst; } ;
struct TYPE_15__ {scalar_t__ format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  HWUploadContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_frame_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_1__**) ; 
 int av_hwframe_transfer_data (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int ff_filter_frame (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwupload_filter_frame(AVFilterLink *link, AVFrame *input)
{
    AVFilterContext *avctx = link->dst;
    AVFilterLink  *outlink = avctx->outputs[0];
    HWUploadContext   *ctx = avctx->priv;
    AVFrame *output = NULL;
    int err;

    if (input->format == outlink->format)
        return ff_filter_frame(outlink, input);

    output = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!output) {
        av_log(ctx, AV_LOG_ERROR, "Failed to allocate frame to upload to.\n");
        err = AVERROR(ENOMEM);
        goto fail;
    }

    output->width  = input->width;
    output->height = input->height;

    err = av_hwframe_transfer_data(output, input, 0);
    if (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Failed to upload frame: %d.\n", err);
        goto fail;
    }

    err = av_frame_copy_props(output, input);
    if (err < 0)
        goto fail;

    av_frame_free(&input);

    return ff_filter_frame(outlink, output);

fail:
    av_frame_free(&input);
    av_frame_free(&output);
    return err;
}