#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * out; int /*<<< orphan*/ * in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_18__ {TYPE_1__* internal; TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_17__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_6__* dst; } ;
struct TYPE_16__ {int rand_shift_init; int flags; int* rand_shift; int /*<<< orphan*/  lfg; scalar_t__ strength; } ;
struct TYPE_15__ {int /*<<< orphan*/ * height; TYPE_4__* param; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ NoiseContext ;
typedef  TYPE_4__ FilterParams ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_RES ; 
 int MAX_SHIFT ; 
 int NOISE_TEMPORAL ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_frame_is_writable (int /*<<< orphan*/ *) ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_filter_frame (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_6__*) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *inpicref)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    NoiseContext *n = ctx->priv;
    ThreadData td;
    AVFrame *out;
    int comp, i;

    if (av_frame_is_writable(inpicref)) {
        out = inpicref;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&inpicref);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, inpicref);
    }

    for (comp = 0; comp < 4; comp++) {
        FilterParams *fp = &n->param[comp];

        if ((!fp->rand_shift_init || (fp->flags & NOISE_TEMPORAL)) && fp->strength) {

            for (i = 0; i < MAX_RES; i++) {
                fp->rand_shift[i] = av_lfg_get(&fp->lfg) & (MAX_SHIFT - 1);
            }
            fp->rand_shift_init = 1;
        }
    }

    td.in = inpicref; td.out = out;
    ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(n->height[0], ff_filter_get_nb_threads(ctx)));
    emms_c();

    if (inpicref != out)
        av_frame_free(&inpicref);
    return ff_filter_frame(outlink, out);
}