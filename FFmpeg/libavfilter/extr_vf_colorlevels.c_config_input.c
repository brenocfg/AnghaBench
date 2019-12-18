#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* priv; } ;
struct TYPE_12__ {int w; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_11__ {TYPE_1__* comp; int /*<<< orphan*/  nb_components; } ;
struct TYPE_10__ {int bpp; int step; int linesize; int /*<<< orphan*/  rgba_map; int /*<<< orphan*/  nb_comp; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ ColorLevelsContext ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int av_get_padded_bits_per_pixel (TYPE_3__ const*) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_fill_rgba_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ColorLevelsContext *s = ctx->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);

    s->nb_comp = desc->nb_components;
    s->bpp = desc->comp[0].depth >> 3;
    s->step = (av_get_padded_bits_per_pixel(desc) >> 3) / s->bpp;
    s->linesize = inlink->w * s->step;
    ff_fill_rgba_map(s->rgba_map, inlink->format);

    return 0;
}