#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  entries; } ;
struct TYPE_20__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_19__ {TYPE_4__* dst; } ;
struct TYPE_18__ {int /*<<< orphan*/  pts; } ;
struct TYPE_17__ {scalar_t__ stats_mode; TYPE_5__* histogram; TYPE_5__* boxes; scalar_t__ nb_boxes; scalar_t__ nb_refs; int /*<<< orphan*/  refs; TYPE_2__* prev_frame; } ;
typedef  TYPE_1__ PaletteGenContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int HIST_SIZE ; 
 scalar_t__ STATS_MODE_DIFF_FRAMES ; 
 scalar_t__ STATS_MODE_SINGLE_FRAMES ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* get_palette_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int update_histogram_diff (TYPE_5__*,TYPE_2__*,TYPE_2__*) ; 
 int update_histogram_frame (TYPE_5__*,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    PaletteGenContext *s = ctx->priv;
    int ret = s->prev_frame ? update_histogram_diff(s->histogram, s->prev_frame, in)
                            : update_histogram_frame(s->histogram, in);

    if (ret > 0)
        s->nb_refs += ret;

    if (s->stats_mode == STATS_MODE_DIFF_FRAMES) {
        av_frame_free(&s->prev_frame);
        s->prev_frame = in;
    } else if (s->stats_mode == STATS_MODE_SINGLE_FRAMES) {
        AVFrame *out;
        int i;

        out = get_palette_frame(ctx);
        out->pts = in->pts;
        av_frame_free(&in);
        ret = ff_filter_frame(ctx->outputs[0], out);
        for (i = 0; i < HIST_SIZE; i++)
            av_freep(&s->histogram[i].entries);
        av_freep(&s->refs);
        s->nb_refs = 0;
        s->nb_boxes = 0;
        memset(s->boxes, 0, sizeof(s->boxes));
        memset(s->histogram, 0, sizeof(s->histogram));
    } else {
        av_frame_free(&in);
    }

    return ret;
}