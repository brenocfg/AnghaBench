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
struct TYPE_10__ {TYPE_2__** inputs; TYPE_1__** outputs; TYPE_3__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  ppsrc; } ;
struct TYPE_8__ {int /*<<< orphan*/  out_formats; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_formats; } ;
typedef  TYPE_3__ FieldMatchContext ;
typedef  int /*<<< orphan*/  AVFilterFormats ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_NONE 156 
#define  AV_PIX_FMT_YUV410P 155 
#define  AV_PIX_FMT_YUV411P 154 
#define  AV_PIX_FMT_YUV420P 153 
#define  AV_PIX_FMT_YUV420P10 152 
#define  AV_PIX_FMT_YUV420P12 151 
#define  AV_PIX_FMT_YUV420P14 150 
#define  AV_PIX_FMT_YUV420P16 149 
#define  AV_PIX_FMT_YUV420P9 148 
#define  AV_PIX_FMT_YUV422P 147 
#define  AV_PIX_FMT_YUV422P10 146 
#define  AV_PIX_FMT_YUV422P12 145 
#define  AV_PIX_FMT_YUV422P14 144 
#define  AV_PIX_FMT_YUV422P16 143 
#define  AV_PIX_FMT_YUV422P9 142 
#define  AV_PIX_FMT_YUV440P 141 
#define  AV_PIX_FMT_YUV440P10 140 
#define  AV_PIX_FMT_YUV440P12 139 
#define  AV_PIX_FMT_YUV444P 138 
#define  AV_PIX_FMT_YUV444P10 137 
#define  AV_PIX_FMT_YUV444P12 136 
#define  AV_PIX_FMT_YUV444P14 135 
#define  AV_PIX_FMT_YUV444P16 134 
#define  AV_PIX_FMT_YUV444P9 133 
#define  AV_PIX_FMT_YUVJ411P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 size_t INPUT_CLEANSRC ; 
 size_t INPUT_MAIN ; 
 int ff_formats_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_make_format_list (int const*) ; 
 int ff_set_common_formats (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int query_formats(AVFilterContext *ctx)
{
    FieldMatchContext *fm = ctx->priv;

    static const enum AVPixelFormat pix_fmts[] = {
        AV_PIX_FMT_YUV444P,  AV_PIX_FMT_YUV422P,  AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_YUV411P,  AV_PIX_FMT_YUV410P,
        AV_PIX_FMT_NONE
    };
    static const enum AVPixelFormat unproc_pix_fmts[] = {
        AV_PIX_FMT_YUV410P, AV_PIX_FMT_YUV411P,
        AV_PIX_FMT_YUV420P, AV_PIX_FMT_YUV422P,
        AV_PIX_FMT_YUV440P, AV_PIX_FMT_YUV444P,
        AV_PIX_FMT_YUVJ420P, AV_PIX_FMT_YUVJ422P,
        AV_PIX_FMT_YUVJ440P, AV_PIX_FMT_YUVJ444P,
        AV_PIX_FMT_YUVJ411P,
        AV_PIX_FMT_YUV420P9, AV_PIX_FMT_YUV422P9, AV_PIX_FMT_YUV444P9,
        AV_PIX_FMT_YUV420P10, AV_PIX_FMT_YUV422P10, AV_PIX_FMT_YUV444P10,
        AV_PIX_FMT_YUV440P10,
        AV_PIX_FMT_YUV444P12, AV_PIX_FMT_YUV422P12, AV_PIX_FMT_YUV420P12,
        AV_PIX_FMT_YUV440P12,
        AV_PIX_FMT_YUV444P14, AV_PIX_FMT_YUV422P14, AV_PIX_FMT_YUV420P14,
        AV_PIX_FMT_YUV420P16, AV_PIX_FMT_YUV422P16, AV_PIX_FMT_YUV444P16,
        AV_PIX_FMT_NONE
    };
    int ret;

    AVFilterFormats *fmts_list = ff_make_format_list(pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    if (!fm->ppsrc) {
        return ff_set_common_formats(ctx, fmts_list);
    }

    if ((ret = ff_formats_ref(fmts_list, &ctx->inputs[INPUT_MAIN]->out_formats)) < 0)
        return ret;
    fmts_list = ff_make_format_list(unproc_pix_fmts);
    if (!fmts_list)
        return AVERROR(ENOMEM);
    if ((ret = ff_formats_ref(fmts_list, &ctx->outputs[0]->in_formats)) < 0)
        return ret;
    if ((ret = ff_formats_ref(fmts_list, &ctx->inputs[INPUT_CLEANSRC]->out_formats)) < 0)
        return ret;
    return 0;
}