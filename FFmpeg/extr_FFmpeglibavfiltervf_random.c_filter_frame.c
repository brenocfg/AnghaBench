#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_11__ {TYPE_4__* dst; } ;
struct TYPE_10__ {int /*<<< orphan*/  pts; } ;
struct TYPE_9__ {int nb_frames_filled; int nb_frames; int /*<<< orphan*/ * pts; TYPE_2__** frames; int /*<<< orphan*/  lfg; } ;
typedef  TYPE_1__ RandomContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    RandomContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int idx;

    if (s->nb_frames_filled < s->nb_frames) {
        s->frames[s->nb_frames_filled] = in;
        s->pts[s->nb_frames_filled++] = in->pts;
        return 0;
    }

    idx = av_lfg_get(&s->lfg) % s->nb_frames;

    out = s->frames[idx];
    out->pts = s->pts[0];
    memmove(&s->pts[0], &s->pts[1], (s->nb_frames - 1) * sizeof(s->pts[0]));
    s->frames[idx] = in;
    s->pts[s->nb_frames - 1] = in->pts;

    return ff_filter_frame(outlink, out);
}