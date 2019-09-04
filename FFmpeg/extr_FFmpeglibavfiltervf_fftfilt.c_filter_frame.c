#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* priv; TYPE_2__** outputs; } ;
struct TYPE_14__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* dst; } ;
struct TYPE_13__ {int nb_planes; int* planewidth; int* planeheight; scalar_t__ eval_mode; int* rdft_hlen; int* rdft_vlen; int** rdft_vdata; int** weight; int* dc; int /*<<< orphan*/  (* irdft_horizontal ) (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ;int /*<<< orphan*/  (* rdft_horizontal ) (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ;} ;
typedef  TYPE_1__ FFTFILTContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ EVAL_MODE_FRAME ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  do_eval (TYPE_1__*,TYPE_2__*,int) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irdft_vertical (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  rdft_vertical (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    FFTFILTContext *s = ctx->priv;
    AVFrame *out;
    int i, j, plane;

    out = ff_get_video_buffer(outlink, inlink->w, inlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    av_frame_copy_props(out, in);

    for (plane = 0; plane < s->nb_planes; plane++) {
        int w = s->planewidth[plane];
        int h = s->planeheight[plane];

        if (s->eval_mode == EVAL_MODE_FRAME)
            do_eval(s, inlink, plane);

        s->rdft_horizontal(s, in, w, h, plane);
        rdft_vertical(s, h, plane);

        /*Change user defined parameters*/
        for (i = 0; i < s->rdft_hlen[plane]; i++)
            for (j = 0; j < s->rdft_vlen[plane]; j++)
                s->rdft_vdata[plane][i * s->rdft_vlen[plane] + j] *=
                  s->weight[plane][i * s->rdft_vlen[plane] + j];

        s->rdft_vdata[plane][0] += s->rdft_hlen[plane] * s->rdft_vlen[plane] * s->dc[plane];

        irdft_vertical(s, h, plane);
        s->irdft_horizontal(s, out, w, h, plane);
    }

    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}