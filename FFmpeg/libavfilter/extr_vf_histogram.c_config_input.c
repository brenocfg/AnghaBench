#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  log2_chroma_h; TYPE_2__* comp; int /*<<< orphan*/  nb_components; } ;
struct TYPE_10__ {int format; void* w; void* h; TYPE_1__* dst; } ;
struct TYPE_9__ {int histogram_size; int mult; int* bg_color; int* fg_color; int fgopacity; int bgopacity; void** planewidth; TYPE_6__* desc; void** planeheight; int /*<<< orphan*/  ncomp; } ;
struct TYPE_8__ {int depth; } ;
struct TYPE_7__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ HistogramContext ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRAP 134 
#define  AV_PIX_FMT_GBRAP10 133 
#define  AV_PIX_FMT_GBRAP12 132 
#define  AV_PIX_FMT_GBRP 131 
#define  AV_PIX_FMT_GBRP10 130 
#define  AV_PIX_FMT_GBRP12 129 
#define  AV_PIX_FMT_GBRP9 128 
 TYPE_6__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  black_gbrp_color ; 
 int /*<<< orphan*/  black_yuva_color ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  white_gbrp_color ; 
 int /*<<< orphan*/  white_yuva_color ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    HistogramContext *h = inlink->dst->priv;

    h->desc  = av_pix_fmt_desc_get(inlink->format);
    h->ncomp = h->desc->nb_components;
    h->histogram_size = 1 << h->desc->comp[0].depth;
    h->mult = h->histogram_size / 256;

    switch (inlink->format) {
    case AV_PIX_FMT_GBRAP12:
    case AV_PIX_FMT_GBRP12:
    case AV_PIX_FMT_GBRAP10:
    case AV_PIX_FMT_GBRP10:
    case AV_PIX_FMT_GBRP9:
    case AV_PIX_FMT_GBRAP:
    case AV_PIX_FMT_GBRP:
        memcpy(h->bg_color, black_gbrp_color, 4);
        memcpy(h->fg_color, white_gbrp_color, 4);
        break;
    default:
        memcpy(h->bg_color, black_yuva_color, 4);
        memcpy(h->fg_color, white_yuva_color, 4);
    }

    h->fg_color[3] = h->fgopacity * 255;
    h->bg_color[3] = h->bgopacity * 255;

    h->planeheight[1] = h->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, h->desc->log2_chroma_h);
    h->planeheight[0] = h->planeheight[3] = inlink->h;
    h->planewidth[1]  = h->planewidth[2]  = AV_CEIL_RSHIFT(inlink->w, h->desc->log2_chroma_w);
    h->planewidth[0]  = h->planewidth[3]  = inlink->w;

    return 0;
}