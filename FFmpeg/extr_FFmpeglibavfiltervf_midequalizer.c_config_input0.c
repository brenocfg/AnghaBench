#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
struct TYPE_11__ {void* w; void* h; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_10__ {int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_9__ {int histogram_size; int /*<<< orphan*/  midequalizer; void* cchange; void** histogram; void*** width; void*** height; int /*<<< orphan*/  nb_planes; } ;
struct TYPE_8__ {int depth; } ;
typedef  TYPE_2__ MidEqualizerContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_CEIL_RSHIFT (void*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midequalizer16 ; 
 int /*<<< orphan*/  midequalizer8 ; 

__attribute__((used)) static int config_input0(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    MidEqualizerContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int vsub, hsub;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);

    hsub = desc->log2_chroma_w;
    vsub = desc->log2_chroma_h;

    s->height[0][0] = s->height[0][3] = inlink->h;
    s->width[0][0]  = s->width[0][3]  = inlink->w;
    s->height[0][1] = s->height[0][2] = AV_CEIL_RSHIFT(inlink->h, vsub);
    s->width[0][1]  = s->width[0][2]  = AV_CEIL_RSHIFT(inlink->w, hsub);

    s->histogram_size = 1 << desc->comp[0].depth;

    s->histogram[0] = av_calloc(s->histogram_size, sizeof(float));
    s->histogram[1] = av_calloc(s->histogram_size, sizeof(float));
    s->cchange      = av_calloc(s->histogram_size, sizeof(unsigned));
    if (!s->histogram[0] || !s->histogram[1] || !s->cchange)
        return AVERROR(ENOMEM);

    if (s->histogram_size == 256) {
        s->midequalizer = midequalizer8;
    } else {
        s->midequalizer = midequalizer16;
    }

    return 0;
}