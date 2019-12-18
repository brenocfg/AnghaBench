#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_7__ {TYPE_2__** outputs; TYPE_1__** inputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_5__ {int /*<<< orphan*/  out_formats; } ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AV_PIX_FMT_PAL8 ; 
 int av_pix_fmt_desc_get_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * av_pix_fmt_desc_next (int /*<<< orphan*/  const*) ; 
 int ff_add_format (int /*<<< orphan*/ **,int) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sws_isSupportedEndiannessConversion (int) ; 
 scalar_t__ sws_isSupportedInput (int) ; 
 scalar_t__ sws_isSupportedOutput (int) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    AVFilterFormats *formats;
    enum AVPixelFormat pix_fmt;
    int ret;

    if (ctx->inputs[0]) {
        const AVPixFmtDescriptor *desc = NULL;
        formats = NULL;
        while ((desc = av_pix_fmt_desc_next(desc))) {
            pix_fmt = av_pix_fmt_desc_get_id(desc);
            if ((sws_isSupportedInput(pix_fmt) ||
                 sws_isSupportedEndiannessConversion(pix_fmt))
                && (ret = ff_add_format(&formats, pix_fmt)) < 0) {
                return ret;
            }
        }
        if ((ret = ff_formats_ref(formats, &ctx->inputs[0]->out_formats)) < 0)
            return ret;
    }
    if (ctx->outputs[0]) {
        const AVPixFmtDescriptor *desc = NULL;
        formats = NULL;
        while ((desc = av_pix_fmt_desc_next(desc))) {
            pix_fmt = av_pix_fmt_desc_get_id(desc);
            if ((sws_isSupportedOutput(pix_fmt) || pix_fmt == AV_PIX_FMT_PAL8 ||
                 sws_isSupportedEndiannessConversion(pix_fmt))
                && (ret = ff_add_format(&formats, pix_fmt)) < 0) {
                return ret;
            }
        }
        if ((ret = ff_formats_ref(formats, &ctx->outputs[0]->in_formats)) < 0)
            return ret;
    }

    return 0;
}