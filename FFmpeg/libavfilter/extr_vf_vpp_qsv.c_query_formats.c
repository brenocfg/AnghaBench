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
struct TYPE_7__ {TYPE_1__** outputs; TYPE_2__** inputs; } ;
struct TYPE_6__ {int /*<<< orphan*/  out_formats; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_formats; } ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
#define  AV_PIX_FMT_NONE 134 
#define  AV_PIX_FMT_NV12 133 
#define  AV_PIX_FMT_P010 132 
#define  AV_PIX_FMT_QSV 131 
#define  AV_PIX_FMT_RGB32 130 
#define  AV_PIX_FMT_YUV420P 129 
#define  AV_PIX_FMT_YUYV422 128 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    int ret;
    AVFilterFormats *in_fmts, *out_fmts;
    static const enum AVPixelFormat in_pix_fmts[] = {
        AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_NV12,
        AV_PIX_FMT_YUYV422,
        AV_PIX_FMT_RGB32,
        AV_PIX_FMT_QSV,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat out_pix_fmts[] = {
        AV_PIX_FMT_NV12,
        AV_PIX_FMT_P010,
        AV_PIX_FMT_QSV,
        AV_PIX_FMT_NONE
    };

    in_fmts  = ff_make_format_list(in_pix_fmts);
    out_fmts = ff_make_format_list(out_pix_fmts);
    ret = ff_formats_ref(in_fmts, &ctx->inputs[0]->out_formats);
    if (ret < 0)
        return ret;
    ret = ff_formats_ref(out_fmts, &ctx->outputs[0]->in_formats);
    if (ret < 0)
        return ret;

    return 0;
}