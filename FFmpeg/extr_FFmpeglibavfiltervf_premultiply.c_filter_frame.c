#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_4__* m; TYPE_4__* a; TYPE_4__* d; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_25__ {TYPE_1__* internal; scalar_t__ is_disabled; TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_24__ {int format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_23__ {scalar_t__ color_range; } ;
struct TYPE_22__ {int /*<<< orphan*/ * height; void** premultiply; scalar_t__ inverse; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ PreMultiplyContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AVCOL_RANGE_JPEG ; 
 scalar_t__ AVCOL_RANGE_MPEG ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRAP 154 
#define  AV_PIX_FMT_GBRAP10 153 
#define  AV_PIX_FMT_GBRAP12 152 
#define  AV_PIX_FMT_GBRAP16 151 
#define  AV_PIX_FMT_GBRP 150 
#define  AV_PIX_FMT_GBRP10 149 
#define  AV_PIX_FMT_GBRP12 148 
#define  AV_PIX_FMT_GBRP14 147 
#define  AV_PIX_FMT_GBRP16 146 
#define  AV_PIX_FMT_GBRP9 145 
#define  AV_PIX_FMT_GRAY10 144 
#define  AV_PIX_FMT_GRAY12 143 
#define  AV_PIX_FMT_GRAY14 142 
#define  AV_PIX_FMT_GRAY16 141 
#define  AV_PIX_FMT_GRAY8 140 
#define  AV_PIX_FMT_GRAY9 139 
#define  AV_PIX_FMT_YUV444P 138 
#define  AV_PIX_FMT_YUV444P10 137 
#define  AV_PIX_FMT_YUV444P12 136 
#define  AV_PIX_FMT_YUV444P14 135 
#define  AV_PIX_FMT_YUV444P16 134 
#define  AV_PIX_FMT_YUV444P9 133 
#define  AV_PIX_FMT_YUVA444P 132 
#define  AV_PIX_FMT_YUVA444P10 131 
#define  AV_PIX_FMT_YUVA444P16 130 
#define  AV_PIX_FMT_YUVA444P9 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* av_frame_clone (TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* premultiply16 ; 
 void* premultiply16offset ; 
 void* premultiply16yuv ; 
 void* premultiply8 ; 
 void* premultiply8offset ; 
 void* premultiply8yuv ; 
 int /*<<< orphan*/  premultiply_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* unpremultiply16 ; 
 void* unpremultiply16offset ; 
 void* unpremultiply16yuv ; 
 void* unpremultiply8 ; 
 void* unpremultiply8offset ; 
 void* unpremultiply8yuv ; 

__attribute__((used)) static int filter_frame(AVFilterContext *ctx,
                        AVFrame **out, AVFrame *base, AVFrame *alpha)
{
    PreMultiplyContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    if (ctx->is_disabled) {
        *out = av_frame_clone(base);
        if (!*out)
            return AVERROR(ENOMEM);
    } else {
        ThreadData td;
        int full, limited;

        *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!*out)
            return AVERROR(ENOMEM);
        av_frame_copy_props(*out, base);

        full = base->color_range == AVCOL_RANGE_JPEG;
        limited = base->color_range == AVCOL_RANGE_MPEG;

        if (s->inverse) {
            switch (outlink->format) {
            case AV_PIX_FMT_YUV444P:
            case AV_PIX_FMT_YUVA444P:
                s->premultiply[0] = full ? unpremultiply8 : unpremultiply8offset;
                s->premultiply[1] = s->premultiply[2] = unpremultiply8yuv;
                break;
            case AV_PIX_FMT_YUVJ444P:
                s->premultiply[0] = unpremultiply8;
                s->premultiply[1] = s->premultiply[2] = unpremultiply8yuv;
                break;
            case AV_PIX_FMT_GBRP:
            case AV_PIX_FMT_GBRAP:
                s->premultiply[0] = s->premultiply[1] = s->premultiply[2] = limited ? unpremultiply8offset : unpremultiply8;
                break;
            case AV_PIX_FMT_YUV444P9:
            case AV_PIX_FMT_YUVA444P9:
            case AV_PIX_FMT_YUV444P10:
            case AV_PIX_FMT_YUVA444P10:
            case AV_PIX_FMT_YUV444P12:
            case AV_PIX_FMT_YUV444P14:
            case AV_PIX_FMT_YUV444P16:
            case AV_PIX_FMT_YUVA444P16:
                s->premultiply[0] = full ? unpremultiply16 : unpremultiply16offset;
                s->premultiply[1] = s->premultiply[2] = unpremultiply16yuv;
                break;
            case AV_PIX_FMT_GBRP9:
            case AV_PIX_FMT_GBRP10:
            case AV_PIX_FMT_GBRAP10:
            case AV_PIX_FMT_GBRP12:
            case AV_PIX_FMT_GBRAP12:
            case AV_PIX_FMT_GBRP14:
            case AV_PIX_FMT_GBRP16:
            case AV_PIX_FMT_GBRAP16:
                s->premultiply[0] = s->premultiply[1] = s->premultiply[2] = limited ? unpremultiply16offset : unpremultiply16;
                break;
            case AV_PIX_FMT_GRAY8:
                s->premultiply[0] = limited ? unpremultiply8offset : unpremultiply8;
                break;
            case AV_PIX_FMT_GRAY9:
            case AV_PIX_FMT_GRAY10:
            case AV_PIX_FMT_GRAY12:
            case AV_PIX_FMT_GRAY14:
            case AV_PIX_FMT_GRAY16:
                s->premultiply[0] = limited ? unpremultiply16offset : unpremultiply16;
                break;
            }
        } else {
            switch (outlink->format) {
            case AV_PIX_FMT_YUV444P:
            case AV_PIX_FMT_YUVA444P:
                s->premultiply[0] = full ? premultiply8 : premultiply8offset;
                s->premultiply[1] = s->premultiply[2] = premultiply8yuv;
                break;
            case AV_PIX_FMT_YUVJ444P:
                s->premultiply[0] = premultiply8;
                s->premultiply[1] = s->premultiply[2] = premultiply8yuv;
                break;
            case AV_PIX_FMT_GBRP:
            case AV_PIX_FMT_GBRAP:
                s->premultiply[0] = s->premultiply[1] = s->premultiply[2] = limited ? premultiply8offset : premultiply8;
                break;
            case AV_PIX_FMT_YUV444P9:
            case AV_PIX_FMT_YUVA444P9:
            case AV_PIX_FMT_YUV444P10:
            case AV_PIX_FMT_YUVA444P10:
            case AV_PIX_FMT_YUV444P12:
            case AV_PIX_FMT_YUV444P14:
            case AV_PIX_FMT_YUV444P16:
            case AV_PIX_FMT_YUVA444P16:
                s->premultiply[0] = full ? premultiply16 : premultiply16offset;
                s->premultiply[1] = s->premultiply[2] = premultiply16yuv;
                break;
            case AV_PIX_FMT_GBRP9:
            case AV_PIX_FMT_GBRP10:
            case AV_PIX_FMT_GBRAP10:
            case AV_PIX_FMT_GBRP12:
            case AV_PIX_FMT_GBRAP12:
            case AV_PIX_FMT_GBRP14:
            case AV_PIX_FMT_GBRP16:
            case AV_PIX_FMT_GBRAP16:
                s->premultiply[0] = s->premultiply[1] = s->premultiply[2] = limited ? premultiply16offset : premultiply16;
                break;
            case AV_PIX_FMT_GRAY8:
                s->premultiply[0] = limited ? premultiply8offset : premultiply8;
                break;
            case AV_PIX_FMT_GRAY9:
            case AV_PIX_FMT_GRAY10:
            case AV_PIX_FMT_GRAY12:
            case AV_PIX_FMT_GRAY14:
            case AV_PIX_FMT_GRAY16:
                s->premultiply[0] = limited ? premultiply16offset : premultiply16;
                break;
            }
        }

        td.d = *out;
        td.a = alpha;
        td.m = base;
        ctx->internal->execute(ctx, premultiply_slice, &td, NULL, FFMIN(s->height[0],
                                                                        ff_filter_get_nb_threads(ctx)));
    }

    return 0;
}