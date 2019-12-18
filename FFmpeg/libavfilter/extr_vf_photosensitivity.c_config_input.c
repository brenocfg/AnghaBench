#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {TYPE_3__* dst; } ;
struct TYPE_5__ {int badness_threshold; int nb_frames; int threshold_multiplier; } ;
typedef  TYPE_1__ PhotosensitivityContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int GRID_SIZE ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    /* const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format); */
    AVFilterContext *ctx = inlink->dst;
    PhotosensitivityContext *s = ctx->priv;

    s->badness_threshold = (int)(GRID_SIZE * GRID_SIZE * 4 * 256 * s->nb_frames * s->threshold_multiplier / 128);

    return 0;
}