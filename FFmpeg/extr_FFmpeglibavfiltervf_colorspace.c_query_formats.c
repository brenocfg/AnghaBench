#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_10__ {TYPE_2__** outputs; TYPE_1__** inputs; TYPE_3__* priv; } ;
struct TYPE_9__ {int const user_format; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_formats; } ;
struct TYPE_7__ {int /*<<< orphan*/  out_formats; } ;
typedef  TYPE_3__ ColorSpaceContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_NONE 140 
#define  AV_PIX_FMT_YUV420P 139 
#define  AV_PIX_FMT_YUV420P10 138 
#define  AV_PIX_FMT_YUV420P12 137 
#define  AV_PIX_FMT_YUV422P 136 
#define  AV_PIX_FMT_YUV422P10 135 
#define  AV_PIX_FMT_YUV422P12 134 
#define  AV_PIX_FMT_YUV444P 133 
#define  AV_PIX_FMT_YUV444P10 132 
#define  AV_PIX_FMT_YUV444P12 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int ff_add_format (int /*<<< orphan*/ **,int const) ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV420P,   AV_PIX_FMT_YUV422P,   AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUV420P10, AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV420P12, AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV444P12,
        AV_PIX_FMT_YUVJ420P,  AV_PIX_FMT_YUVJ422P,  AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_NONE
    };
    int res;
    ColorSpaceContext *s = ctx->priv;
    AVFilterFormats *formats = ff_make_format_list(pix_fmts);

    if (!formats)
        return AVERROR(ENOMEM);
    if (s->user_format == AV_PIX_FMT_NONE)
        return ff_set_common_formats(ctx, formats);
    res = ff_formats_ref(formats, &ctx->inputs[0]->out_formats);
    if (res < 0)
        return res;
    formats = NULL;
    res = ff_add_format(&formats, s->user_format);
    if (res < 0)
        return res;

    return ff_formats_ref(formats, &ctx->outputs[0]->in_formats);
}