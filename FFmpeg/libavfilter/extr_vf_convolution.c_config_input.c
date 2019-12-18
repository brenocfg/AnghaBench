#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* filter; TYPE_3__* priv; } ;
struct TYPE_15__ {int /*<<< orphan*/  format; void* h; void* w; TYPE_6__* dst; } ;
struct TYPE_14__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; TYPE_1__* comp; } ;
struct TYPE_13__ {int depth; int max; int nb_planes; int bpc; scalar_t__* mode; int* size; int /*<<< orphan*/ * filter; int /*<<< orphan*/  nb_threads; void** planeheight; void** planewidth; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int depth; } ;
typedef  TYPE_3__ ConvolutionContext ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ MATRIX_COLUMN ; 
 scalar_t__ MATRIX_ROW ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_convolution_init_x86 (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 int /*<<< orphan*/  filter16_3x3 ; 
 int /*<<< orphan*/  filter16_5x5 ; 
 int /*<<< orphan*/  filter16_7x7 ; 
 int /*<<< orphan*/  filter16_column ; 
 int /*<<< orphan*/  filter16_prewitt ; 
 int /*<<< orphan*/  filter16_roberts ; 
 int /*<<< orphan*/  filter16_row ; 
 int /*<<< orphan*/  filter16_sobel ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ConvolutionContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int p;

    s->depth = desc->comp[0].depth;
    s->max = (1 << s->depth) - 1;

    s->planewidth[1] = s->planewidth[2] = AV_CEIL_RSHIFT(inlink->w, desc->log2_chroma_w);
    s->planewidth[0] = s->planewidth[3] = inlink->w;
    s->planeheight[1] = s->planeheight[2] = AV_CEIL_RSHIFT(inlink->h, desc->log2_chroma_h);
    s->planeheight[0] = s->planeheight[3] = inlink->h;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);
    s->nb_threads = ff_filter_get_nb_threads(ctx);
    s->bpc = (s->depth + 7) / 8;

    if (!strcmp(ctx->filter->name, "convolution")) {
        if (s->depth > 8) {
            for (p = 0; p < s->nb_planes; p++) {
                if (s->mode[p] == MATRIX_ROW)
                    s->filter[p] = filter16_row;
                else if (s->mode[p] == MATRIX_COLUMN)
                    s->filter[p] = filter16_column;
                else if (s->size[p] == 3)
                    s->filter[p] = filter16_3x3;
                else if (s->size[p] == 5)
                    s->filter[p] = filter16_5x5;
                else if (s->size[p] == 7)
                    s->filter[p] = filter16_7x7;
            }
        }
#if CONFIG_CONVOLUTION_FILTER && ARCH_X86_64
        ff_convolution_init_x86(s);
#endif
    } else if (!strcmp(ctx->filter->name, "prewitt")) {
        if (s->depth > 8)
            for (p = 0; p < s->nb_planes; p++)
                s->filter[p] = filter16_prewitt;
    } else if (!strcmp(ctx->filter->name, "roberts")) {
        if (s->depth > 8)
            for (p = 0; p < s->nb_planes; p++)
                s->filter[p] = filter16_roberts;
    } else if (!strcmp(ctx->filter->name, "sobel")) {
        if (s->depth > 8)
            for (p = 0; p < s->nb_planes; p++)
                s->filter[p] = filter16_sobel;
    }

    return 0;
}