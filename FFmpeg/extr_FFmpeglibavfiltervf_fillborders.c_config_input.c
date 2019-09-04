#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_15__ {TYPE_3__* priv; } ;
struct TYPE_14__ {int h; int w; int /*<<< orphan*/  format; TYPE_6__* dst; } ;
struct TYPE_13__ {int log2_chroma_h; int log2_chroma_w; int flags; TYPE_1__* comp; int /*<<< orphan*/  nb_components; } ;
struct TYPE_12__ {int depth; int* planeheight; int* planewidth; int left; int right; int top; int bottom; int mode; int /*<<< orphan*/ * yuv_color; int /*<<< orphan*/ * fill; int /*<<< orphan*/ * rgba_color; int /*<<< orphan*/  fillborders; TYPE_2__* borders; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_11__ {int left; int right; int top; int bottom; } ;
struct TYPE_10__ {int depth; } ;
typedef  TYPE_3__ FillBordersContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 size_t A ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 size_t B ; 
 int /*<<< orphan*/  EINVAL ; 
#define  FM_FIXED 130 
#define  FM_MIRROR 129 
#define  FM_SMEAR 128 
 size_t G ; 
 size_t R ; 
 int /*<<< orphan*/  RGB_TO_U_CCIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB_TO_V_CCIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB_TO_Y_CCIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t U ; 
 size_t V ; 
 size_t Y ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_borders16 ; 
 int /*<<< orphan*/  fixed_borders8 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mirror_borders16 ; 
 int /*<<< orphan*/  mirror_borders8 ; 
 int /*<<< orphan*/  smear_borders16 ; 
 int /*<<< orphan*/  smear_borders8 ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    FillBordersContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    s->nb_planes = desc->nb_components;
    s->depth = desc->comp[0].depth;

    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;
    s->planewidth[1]  = s->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0]  = s->planewidth[3]  = inlink->w;

    s->borders[0].left   = s->borders[3].left = s->left;
    s->borders[0].right  = s->borders[3].right = s->right;
    s->borders[0].top    = s->borders[3].top = s->top;
    s->borders[0].bottom = s->borders[3].bottom = s->bottom;

    s->borders[1].left   = s->left >> desc->log2_chroma_w;
    s->borders[1].right  = s->right >> desc->log2_chroma_w;
    s->borders[1].top    = s->top >> desc->log2_chroma_h;
    s->borders[1].bottom = s->bottom >> desc->log2_chroma_h;

    s->borders[2].left   = s->left >> desc->log2_chroma_w;
    s->borders[2].right  = s->right >> desc->log2_chroma_w;
    s->borders[2].top    = s->top >> desc->log2_chroma_h;
    s->borders[2].bottom = s->bottom >> desc->log2_chroma_h;

    if (inlink->w < s->left + s->right ||
        inlink->w <= s->left ||
        inlink->w <= s->right ||
        inlink->h < s->top + s->bottom ||
        inlink->h <= s->top ||
        inlink->h <= s->bottom ||
        inlink->w < s->left * 2 ||
        inlink->w < s->right * 2 ||
        inlink->h < s->top * 2 ||
        inlink->h < s->bottom * 2) {
        av_log(ctx, AV_LOG_ERROR, "Borders are bigger than input frame size.\n");
        return AVERROR(EINVAL);
    }

    switch (s->mode) {
    case FM_SMEAR:  s->fillborders = s->depth <= 8 ? smear_borders8  : smear_borders16;  break;
    case FM_MIRROR: s->fillborders = s->depth <= 8 ? mirror_borders8 : mirror_borders16; break;
    case FM_FIXED:  s->fillborders = s->depth <= 8 ? fixed_borders8  : fixed_borders16;  break;
    }

    s->yuv_color[Y] = RGB_TO_Y_CCIR(s->rgba_color[R], s->rgba_color[G], s->rgba_color[B]);
    s->yuv_color[U] = RGB_TO_U_CCIR(s->rgba_color[R], s->rgba_color[G], s->rgba_color[B], 0);
    s->yuv_color[V] = RGB_TO_V_CCIR(s->rgba_color[R], s->rgba_color[G], s->rgba_color[B], 0);
    s->yuv_color[A] = s->rgba_color[A];

    if (desc->flags & AV_PIX_FMT_FLAG_RGB) {
        uint8_t rgba_map[4];
        int i;

        ff_fill_rgba_map(rgba_map, inlink->format);
        for (i = 0; i < 4; i++)
            s->fill[rgba_map[i]] = s->rgba_color[i];
    } else {
        memcpy(s->fill, s->yuv_color, sizeof(s->yuv_color));
    }

    return 0;
}