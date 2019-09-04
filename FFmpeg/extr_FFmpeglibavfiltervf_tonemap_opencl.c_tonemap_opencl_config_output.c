#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ output_format; } ;
struct TYPE_9__ {scalar_t__ format; TYPE_1__ ocf; } ;
typedef  TYPE_2__ TonemapOpenCLContext ;
struct TYPE_11__ {TYPE_2__* priv; } ;
struct TYPE_10__ {TYPE_4__* src; } ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_NONE ; 
 scalar_t__ AV_PIX_FMT_NV12 ; 
 scalar_t__ AV_PIX_FMT_P010 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_opencl_filter_config_output (TYPE_3__*) ; 

__attribute__((used)) static int tonemap_opencl_config_output(AVFilterLink *outlink)
{
    AVFilterContext *avctx = outlink->src;
    TonemapOpenCLContext *s = avctx->priv;
    int ret;
    if (s->format == AV_PIX_FMT_NONE)
        av_log(avctx, AV_LOG_WARNING, "format not set, use default format NV12\n");
    else {
      if (s->format != AV_PIX_FMT_P010 &&
          s->format != AV_PIX_FMT_NV12) {
        av_log(avctx, AV_LOG_ERROR, "unsupported output format,"
               "only p010/nv12 supported now\n");
        return AVERROR(EINVAL);
      }
    }

    s->ocf.output_format = s->format == AV_PIX_FMT_NONE ? AV_PIX_FMT_NV12 : s->format;
    ret = ff_opencl_filter_config_output(outlink);
    if (ret < 0)
        return ret;

    return 0;
}