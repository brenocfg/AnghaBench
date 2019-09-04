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
struct TYPE_12__ {scalar_t__ h; TYPE_5__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_11__ {TYPE_1__* comp; } ;
struct TYPE_10__ {scalar_t__ end; scalar_t__ start; int min_range; int mac; int max_peak_diff; int mhd; int max_period_diff; int mpd; int max_start_diff; int msd; int white; int wth; int black; int bth; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ ReadEIA608Context ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    AVFilterContext *ctx = inlink->dst;
    ReadEIA608Context *s = ctx->priv;
    int depth = desc->comp[0].depth;

    if (s->end >= inlink->h) {
        av_log(ctx, AV_LOG_WARNING, "Last line to scan too large, clipping.\n");
        s->end = inlink->h - 1;
    }

    if (s->start > s->end) {
        av_log(ctx, AV_LOG_ERROR, "Invalid range.\n");
        return AVERROR(EINVAL);
    }

    s->min_range = s->mac * ((1 << depth) - 1);
    s->max_peak_diff = s->mhd * ((1 << depth) - 1);
    s->max_period_diff = s->mpd * ((1 << depth) - 1);
    s->max_start_diff = s->msd * ((1 << depth) - 1);
    s->white = s->wth * ((1 << depth) - 1);
    s->black = s->bth * ((1 << depth) - 1);

    return 0;
}