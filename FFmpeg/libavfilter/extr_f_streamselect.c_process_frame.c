#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ frame_count_in; int /*<<< orphan*/  time_base; } ;
struct TYPE_17__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  pts; } ;
struct TYPE_16__ {int nb_inputs; TYPE_9__** outputs; } ;
struct TYPE_15__ {scalar_t__ pts; } ;
struct TYPE_14__ {TYPE_1__* opaque; TYPE_4__* parent; } ;
struct TYPE_13__ {int nb_map; int* map; scalar_t__* last_pts; TYPE_6__ fs; scalar_t__ is_audio; TYPE_3__** frames; } ;
typedef  TYPE_1__ StreamSelectContext ;
typedef  TYPE_2__ FFFrameSync ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_frame_clone (TYPE_3__*) ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_9__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ff_filter_set_ready (TYPE_4__*,int) ; 
 int ff_framesync_get_frame (TYPE_6__*,int,TYPE_3__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_frame(FFFrameSync *fs)
{
    AVFilterContext *ctx = fs->parent;
    StreamSelectContext *s = fs->opaque;
    AVFrame **in = s->frames;
    int i, j, ret = 0, have_out = 0;

    for (i = 0; i < ctx->nb_inputs; i++) {
        if ((ret = ff_framesync_get_frame(&s->fs, i, &in[i], 0)) < 0)
            return ret;
    }

    for (j = 0; j < ctx->nb_inputs; j++) {
        for (i = 0; i < s->nb_map; i++) {
            if (s->map[i] == j) {
                AVFrame *out;

                if (s->is_audio && s->last_pts[j] == in[j]->pts &&
                    ctx->outputs[i]->frame_count_in > 0)
                    continue;
                out = av_frame_clone(in[j]);
                if (!out)
                    return AVERROR(ENOMEM);

                out->pts = av_rescale_q(s->fs.pts, s->fs.time_base, ctx->outputs[i]->time_base);
                s->last_pts[j] = in[j]->pts;
                ret = ff_filter_frame(ctx->outputs[i], out);
                have_out = 1;
                if (ret < 0)
                    return ret;
            }
        }
    }

    if (!have_out)
        ff_filter_set_ready(ctx, 100);
    return ret;
}