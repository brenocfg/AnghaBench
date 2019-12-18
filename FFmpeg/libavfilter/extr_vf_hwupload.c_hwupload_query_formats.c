#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_18__ {TYPE_2__** outputs; TYPE_1__** inputs; int /*<<< orphan*/  hw_device_ctx; TYPE_3__* priv; } ;
struct TYPE_17__ {int* valid_sw_formats; int* valid_hw_formats; } ;
struct TYPE_16__ {TYPE_10__* hwdevice_ref; int /*<<< orphan*/ * hwdevice; } ;
struct TYPE_15__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_14__ {int /*<<< orphan*/  out_formats; } ;
struct TYPE_13__ {scalar_t__ data; } ;
typedef  TYPE_3__ HWUploadContext ;
typedef  TYPE_4__ AVHWFramesConstraints ;
typedef  int /*<<< orphan*/  AVHWDeviceContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int const AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_10__* av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_10__**) ; 
 TYPE_4__* av_hwdevice_get_hwframe_constraints (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_hwframe_constraints_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_add_format (int /*<<< orphan*/ **,int const) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int hwupload_query_formats(AVFilterContext *avctx)
{
    HWUploadContext *ctx = avctx->priv;
    AVHWFramesConstraints *constraints = NULL;
    const enum AVPixelFormat *input_pix_fmts, *output_pix_fmts;
    AVFilterFormats *input_formats = NULL;
    int err, i;

    if (!avctx->hw_device_ctx) {
        av_log(ctx, AV_LOG_ERROR, "A hardware device reference is required "
               "to upload frames to.\n");
        return AVERROR(EINVAL);
    }

    ctx->hwdevice_ref = av_buffer_ref(avctx->hw_device_ctx);
    if (!ctx->hwdevice_ref)
        return AVERROR(ENOMEM);
    ctx->hwdevice = (AVHWDeviceContext*)ctx->hwdevice_ref->data;

    constraints = av_hwdevice_get_hwframe_constraints(ctx->hwdevice_ref, NULL);
    if (!constraints) {
        err = AVERROR(EINVAL);
        goto fail;
    }

    input_pix_fmts  = constraints->valid_sw_formats;
    output_pix_fmts = constraints->valid_hw_formats;

    input_formats = ff_make_format_list(output_pix_fmts);
    if (!input_formats) {
        err = AVERROR(ENOMEM);
        goto fail;
    }
    if (input_pix_fmts) {
        for (i = 0; input_pix_fmts[i] != AV_PIX_FMT_NONE; i++) {
            err = ff_add_format(&input_formats, input_pix_fmts[i]);
            if (err < 0)
                goto fail;
        }
    }

    if ((err = ff_formats_ref(input_formats, &avctx->inputs[0]->out_formats)) < 0 ||
        (err = ff_formats_ref(ff_make_format_list(output_pix_fmts),
                              &avctx->outputs[0]->in_formats)) < 0)
        goto fail;

    av_hwframe_constraints_free(&constraints);
    return 0;

fail:
    av_buffer_unref(&ctx->hwdevice_ref);
    av_hwframe_constraints_free(&constraints);
    return err;
}