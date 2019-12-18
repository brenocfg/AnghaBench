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
struct TYPE_13__ {int steps_y; } ;
struct TYPE_9__ {int /*<<< orphan*/  hsub; TYPE_5__ chroma; TYPE_5__ luma; int /*<<< orphan*/  nb_threads; int /*<<< orphan*/  vsub; } ;
typedef  TYPE_1__ UnsharpContext ;
struct TYPE_12__ {TYPE_1__* priv; } ;
struct TYPE_11__ {int h; int /*<<< orphan*/  w; TYPE_4__* dst; int /*<<< orphan*/  format; } ;
struct TYPE_10__ {int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_4__*) ; 
 int init_filter_param (TYPE_4__*,TYPE_5__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    UnsharpContext *s = inlink->dst->priv;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int ret;

    s->hsub = desc->log2_chroma_w;
    s->vsub = desc->log2_chroma_h;

    // ensure (height / nb_threads) > 4 * steps_y,
    // so that we don't have too much overlap between two threads
    s->nb_threads = FFMIN(ff_filter_get_nb_threads(inlink->dst),
                          inlink->h / (4 * s->luma.steps_y));

    ret = init_filter_param(inlink->dst, &s->luma,   "luma",   inlink->w);
    if (ret < 0)
        return ret;
    ret = init_filter_param(inlink->dst, &s->chroma, "chroma", AV_CEIL_RSHIFT(inlink->w, s->hsub));
    if (ret < 0)
        return ret;

    return 0;
}