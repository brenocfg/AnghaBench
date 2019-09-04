#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* priv; } ;
struct TYPE_10__ {void* w; void* h; int /*<<< orphan*/  format; TYPE_4__* dst; } ;
struct TYPE_9__ {int nb_components; int flags; int log2_chroma_w; int log2_chroma_h; } ;
struct TYPE_8__ {int nb_planes; int nb_components; int* blank; int step; void** width; void** height; int /*<<< orphan*/  displace; } ;
typedef  TYPE_1__ DisplaceContext ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 void* AV_CEIL_RSHIFT (void*,int) ; 
 int AV_PIX_FMT_FLAG_RGB ; 
 int av_get_padded_bits_per_pixel (TYPE_2__ const*) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  displace_packed ; 
 int /*<<< orphan*/  displace_planar ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    DisplaceContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int vsub, hsub;

    s->nb_planes = av_pix_fmt_count_planes(inlink->format);
    s->nb_components = desc->nb_components;

    if (s->nb_planes > 1 || s->nb_components == 1)
        s->displace = displace_planar;
    else
        s->displace = displace_packed;

    if (!(desc->flags & AV_PIX_FMT_FLAG_RGB)) {
        s->blank[1] = s->blank[2] = 128;
        s->blank[0] = 16;
    }

    s->step = av_get_padded_bits_per_pixel(desc) >> 3;
    hsub = desc->log2_chroma_w;
    vsub = desc->log2_chroma_h;
    s->height[1] = s->height[2] = AV_CEIL_RSHIFT(inlink->h, vsub);
    s->height[0] = s->height[3] = inlink->h;
    s->width[1]  = s->width[2]  = AV_CEIL_RSHIFT(inlink->w, hsub);
    s->width[0]  = s->width[3]  = inlink->w;

    return 0;
}