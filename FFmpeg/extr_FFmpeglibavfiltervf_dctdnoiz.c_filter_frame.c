#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_24__ {TYPE_1__* internal; TYPE_5__** outputs; TYPE_3__* priv; } ;
struct TYPE_23__ {int w; int h; TYPE_6__* dst; } ;
struct TYPE_22__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_21__ {int pr_width; int pr_height; int /*<<< orphan*/  p_linesize; int /*<<< orphan*/ ** cbuf; int /*<<< orphan*/  (* color_correlation ) (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  nb_threads; int /*<<< orphan*/  (* color_decorrelation ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int,int) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* execute ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DCTdnoizContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_4__*) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    DCTdnoizContext *s = ctx->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    int direct, plane;
    AVFrame *out;

    if (av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        direct = 0;
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    s->color_decorrelation(s->cbuf[0], s->p_linesize,
                           (const uint8_t **)in->data, in->linesize[0],
                           s->pr_width, s->pr_height);
    for (plane = 0; plane < 3; plane++) {
        ThreadData td = {
            .src = s->cbuf[0][plane],
            .dst = s->cbuf[1][plane],
        };
        ctx->internal->execute(ctx, filter_slice, &td, NULL, s->nb_threads);
    }
    s->color_correlation(out->data, out->linesize[0],
                         s->cbuf[1], s->p_linesize,
                         s->pr_width, s->pr_height);

    if (!direct) {
        int y;
        uint8_t *dst = out->data[0];
        const uint8_t *src = in->data[0];
        const int dst_linesize = out->linesize[0];
        const int src_linesize = in->linesize[0];
        const int hpad = (inlink->w - s->pr_width) * 3;
        const int vpad = (inlink->h - s->pr_height);

        if (hpad) {
            uint8_t       *dstp = dst + s->pr_width * 3;
            const uint8_t *srcp = src + s->pr_width * 3;

            for (y = 0; y < s->pr_height; y++) {
                memcpy(dstp, srcp, hpad);
                dstp += dst_linesize;
                srcp += src_linesize;
            }
        }
        if (vpad) {
            uint8_t       *dstp = dst + s->pr_height * dst_linesize;
            const uint8_t *srcp = src + s->pr_height * src_linesize;

            for (y = 0; y < vpad; y++) {
                memcpy(dstp, srcp, inlink->w * 3);
                dstp += dst_linesize;
                srcp += src_linesize;
            }
        }

        av_frame_free(&in);
    }

    return ff_filter_frame(outlink, out);
}