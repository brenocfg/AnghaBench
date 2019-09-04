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
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_NONE 130 
#define  AV_PIX_FMT_PAL8 129 
#define  AV_PIX_FMT_RGB32 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat in_fmts[]    = {AV_PIX_FMT_RGB32, AV_PIX_FMT_NONE};
    static const enum AVPixelFormat inpal_fmts[] = {AV_PIX_FMT_RGB32, AV_PIX_FMT_NONE};
    static const enum AVPixelFormat out_fmts[]   = {AV_PIX_FMT_PAL8,  AV_PIX_FMT_NONE};
    int ret;
    AVFilterFormats *in    = ff_make_format_list(in_fmts);
    AVFilterFormats *inpal = ff_make_format_list(inpal_fmts);
    AVFilterFormats *out   = ff_make_format_list(out_fmts);
    if (!in || !inpal || !out) {
        av_freep(&in);
        av_freep(&inpal);
        av_freep(&out);
        return AVERROR(ENOMEM);
    }
    if ((ret = ff_formats_ref(in   , &ctx->inputs[0]->out_formats)) < 0 ||
        (ret = ff_formats_ref(inpal, &ctx->inputs[1]->out_formats)) < 0 ||
        (ret = ff_formats_ref(out  , &ctx->outputs[0]->in_formats)) < 0)
        return ret;
    return 0;
}