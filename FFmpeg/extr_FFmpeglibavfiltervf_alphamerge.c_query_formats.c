#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_12__ {TYPE_2__** outputs; TYPE_1__** inputs; } ;
struct TYPE_11__ {struct TYPE_11__* formats; } ;
struct TYPE_10__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_9__ {int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_ABGR 137 
#define  AV_PIX_FMT_ARGB 136 
#define  AV_PIX_FMT_BGRA 135 
#define  AV_PIX_FMT_GBRAP 134 
#define  AV_PIX_FMT_GRAY8 133 
#define  AV_PIX_FMT_NONE 132 
#define  AV_PIX_FMT_RGBA 131 
#define  AV_PIX_FMT_YUVA420P 130 
#define  AV_PIX_FMT_YUVA422P 129 
#define  AV_PIX_FMT_YUVA444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int ff_formats_ref (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat main_fmts[] = {
        AV_PIX_FMT_YUVA444P, AV_PIX_FMT_YUVA422P, AV_PIX_FMT_YUVA420P,
        AV_PIX_FMT_GBRAP,
        AV_PIX_FMT_RGBA, AV_PIX_FMT_BGRA, AV_PIX_FMT_ARGB, AV_PIX_FMT_ABGR,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat alpha_fmts[] = { AV_PIX_FMT_GRAY8, AV_PIX_FMT_NONE };
    AVFilterFormats *main_formats = NULL, *alpha_formats = NULL;
    int ret;

    if (!(main_formats = ff_make_format_list(main_fmts)) ||
        !(alpha_formats = ff_make_format_list(alpha_fmts))) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    if ((ret = ff_formats_ref(main_formats , &ctx->inputs[0]->out_formats)) < 0 ||
        (ret = ff_formats_ref(alpha_formats, &ctx->inputs[1]->out_formats)) < 0 ||
        (ret = ff_formats_ref(main_formats , &ctx->outputs[0]->in_formats)) < 0)
            goto fail;
    return 0;
fail:
    if (main_formats)
        av_freep(&main_formats->formats);
    av_freep(&main_formats);
    if (alpha_formats)
        av_freep(&alpha_formats->formats);
    av_freep(&alpha_formats);
    return ret;
}