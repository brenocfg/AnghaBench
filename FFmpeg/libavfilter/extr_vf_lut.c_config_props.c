#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_16__ {TYPE_2__* priv; } ;
struct TYPE_15__ {int w; int h; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_14__ {int flags; int nb_components; TYPE_1__* comp; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
struct TYPE_13__ {int* var_values; int is_16bit; int is_yuv; int is_rgb; int is_planar; int step; int* comp_expr_str; int** lut; int /*<<< orphan*/ ** comp_expr; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_12__ {int depth; } ;
typedef  TYPE_2__ LutContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
#define  AV_PIX_FMT_RGB48LE 164 
#define  AV_PIX_FMT_RGBA64LE 163 
#define  AV_PIX_FMT_YUV410P 162 
#define  AV_PIX_FMT_YUV411P 161 
#define  AV_PIX_FMT_YUV420P 160 
#define  AV_PIX_FMT_YUV420P10LE 159 
#define  AV_PIX_FMT_YUV420P12LE 158 
#define  AV_PIX_FMT_YUV420P14LE 157 
#define  AV_PIX_FMT_YUV420P16LE 156 
#define  AV_PIX_FMT_YUV420P9LE 155 
#define  AV_PIX_FMT_YUV422P 154 
#define  AV_PIX_FMT_YUV422P10LE 153 
#define  AV_PIX_FMT_YUV422P12LE 152 
#define  AV_PIX_FMT_YUV422P14LE 151 
#define  AV_PIX_FMT_YUV422P16LE 150 
#define  AV_PIX_FMT_YUV422P9LE 149 
#define  AV_PIX_FMT_YUV440P 148 
#define  AV_PIX_FMT_YUV440P10LE 147 
#define  AV_PIX_FMT_YUV440P12LE 146 
#define  AV_PIX_FMT_YUV444P 145 
#define  AV_PIX_FMT_YUV444P10LE 144 
#define  AV_PIX_FMT_YUV444P12LE 143 
#define  AV_PIX_FMT_YUV444P14LE 142 
#define  AV_PIX_FMT_YUV444P16LE 141 
#define  AV_PIX_FMT_YUV444P9LE 140 
#define  AV_PIX_FMT_YUVA420P 139 
#define  AV_PIX_FMT_YUVA420P10LE 138 
#define  AV_PIX_FMT_YUVA420P16LE 137 
#define  AV_PIX_FMT_YUVA420P9LE 136 
#define  AV_PIX_FMT_YUVA422P 135 
#define  AV_PIX_FMT_YUVA422P10LE 134 
#define  AV_PIX_FMT_YUVA422P16LE 133 
#define  AV_PIX_FMT_YUVA422P9LE 132 
#define  AV_PIX_FMT_YUVA444P 131 
#define  AV_PIX_FMT_YUVA444P10LE 130 
#define  AV_PIX_FMT_YUVA444P16LE 129 
#define  AV_PIX_FMT_YUVA444P9LE 128 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (int*) ; 
 size_t U ; 
 size_t V ; 
 size_t VAR_CLIPVAL ; 
 size_t VAR_H ; 
 size_t VAR_MAXVAL ; 
 size_t VAR_MINVAL ; 
 size_t VAR_NEGVAL ; 
 size_t VAR_VAL ; 
 size_t VAR_W ; 
 size_t Y ; 
 void* av_clip (int,int,int) ; 
 double av_expr_eval (int /*<<< orphan*/ *,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int av_get_bits_per_pixel (TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_fmt_is_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funcs1 ; 
 int /*<<< orphan*/  funcs1_names ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  rgb_pix_fmts ; 
 int /*<<< orphan*/  var_names ; 
 int /*<<< orphan*/  yuv_pix_fmts ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    LutContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    uint8_t rgba_map[4]; /* component index -> RGBA color index map */
    int min[4], max[4];
    int val, color, ret;

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;

    s->var_values[VAR_W] = inlink->w;
    s->var_values[VAR_H] = inlink->h;
    s->is_16bit = desc->comp[0].depth > 8;

    switch (inlink->format) {
    case AV_PIX_FMT_YUV410P:
    case AV_PIX_FMT_YUV411P:
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUV440P:
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVA420P:
    case AV_PIX_FMT_YUVA422P:
    case AV_PIX_FMT_YUVA444P:
    case AV_PIX_FMT_YUV420P9LE:
    case AV_PIX_FMT_YUV422P9LE:
    case AV_PIX_FMT_YUV444P9LE:
    case AV_PIX_FMT_YUVA420P9LE:
    case AV_PIX_FMT_YUVA422P9LE:
    case AV_PIX_FMT_YUVA444P9LE:
    case AV_PIX_FMT_YUV420P10LE:
    case AV_PIX_FMT_YUV422P10LE:
    case AV_PIX_FMT_YUV440P10LE:
    case AV_PIX_FMT_YUV444P10LE:
    case AV_PIX_FMT_YUVA420P10LE:
    case AV_PIX_FMT_YUVA422P10LE:
    case AV_PIX_FMT_YUVA444P10LE:
    case AV_PIX_FMT_YUV420P12LE:
    case AV_PIX_FMT_YUV422P12LE:
    case AV_PIX_FMT_YUV440P12LE:
    case AV_PIX_FMT_YUV444P12LE:
    case AV_PIX_FMT_YUV420P14LE:
    case AV_PIX_FMT_YUV422P14LE:
    case AV_PIX_FMT_YUV444P14LE:
    case AV_PIX_FMT_YUV420P16LE:
    case AV_PIX_FMT_YUV422P16LE:
    case AV_PIX_FMT_YUV444P16LE:
    case AV_PIX_FMT_YUVA420P16LE:
    case AV_PIX_FMT_YUVA422P16LE:
    case AV_PIX_FMT_YUVA444P16LE:
        min[Y] = 16 * (1 << (desc->comp[0].depth - 8));
        min[U] = 16 * (1 << (desc->comp[1].depth - 8));
        min[V] = 16 * (1 << (desc->comp[2].depth - 8));
        min[A] = 0;
        max[Y] = 235 * (1 << (desc->comp[0].depth - 8));
        max[U] = 240 * (1 << (desc->comp[1].depth - 8));
        max[V] = 240 * (1 << (desc->comp[2].depth - 8));
        max[A] = (1 << desc->comp[0].depth) - 1;
        break;
    case AV_PIX_FMT_RGB48LE:
    case AV_PIX_FMT_RGBA64LE:
        min[0] = min[1] = min[2] = min[3] = 0;
        max[0] = max[1] = max[2] = max[3] = 65535;
        break;
    default:
        min[0] = min[1] = min[2] = min[3] = 0;
        max[0] = max[1] = max[2] = max[3] = 255 * (1 << (desc->comp[0].depth - 8));
    }

    s->is_yuv = s->is_rgb = 0;
    s->is_planar = desc->flags & AV_PIX_FMT_FLAG_PLANAR;
    if      (ff_fmt_is_in(inlink->format, yuv_pix_fmts)) s->is_yuv = 1;
    else if (ff_fmt_is_in(inlink->format, rgb_pix_fmts)) s->is_rgb = 1;

    if (s->is_rgb) {
        ff_fill_rgba_map(rgba_map, inlink->format);
        s->step = av_get_bits_per_pixel(desc) >> 3;
        if (s->is_16bit) {
            s->step = s->step >> 1;
        }
    }

    for (color = 0; color < desc->nb_components; color++) {
        double res;
        int comp = s->is_rgb ? rgba_map[color] : color;

        /* create the parsed expression */
        av_expr_free(s->comp_expr[color]);
        s->comp_expr[color] = NULL;
        ret = av_expr_parse(&s->comp_expr[color], s->comp_expr_str[color],
                            var_names, funcs1_names, funcs1, NULL, NULL, 0, ctx);
        if (ret < 0) {
            av_log(ctx, AV_LOG_ERROR,
                   "Error when parsing the expression '%s' for the component %d and color %d.\n",
                   s->comp_expr_str[comp], comp, color);
            return AVERROR(EINVAL);
        }

        /* compute the lut */
        s->var_values[VAR_MAXVAL] = max[color];
        s->var_values[VAR_MINVAL] = min[color];

        for (val = 0; val < FF_ARRAY_ELEMS(s->lut[comp]); val++) {
            s->var_values[VAR_VAL] = val;
            s->var_values[VAR_CLIPVAL] = av_clip(val, min[color], max[color]);
            s->var_values[VAR_NEGVAL] =
                av_clip(min[color] + max[color] - s->var_values[VAR_VAL],
                        min[color], max[color]);

            res = av_expr_eval(s->comp_expr[color], s->var_values, s);
            if (isnan(res)) {
                av_log(ctx, AV_LOG_ERROR,
                       "Error when evaluating the expression '%s' for the value %d for the component %d.\n",
                       s->comp_expr_str[color], val, comp);
                return AVERROR(EINVAL);
            }
            s->lut[comp][val] = av_clip((int)res, 0, max[A]);
            av_log(ctx, AV_LOG_DEBUG, "val[%d][%d] = %d\n", comp, val, s->lut[comp][val]);
        }
    }

    return 0;
}