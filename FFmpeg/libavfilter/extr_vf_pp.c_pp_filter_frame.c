#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_18__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_17__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_16__ {int pict_type; int /*<<< orphan*/  linesize; scalar_t__ data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_15__ {size_t mode_id; int /*<<< orphan*/  pp_ctx; int /*<<< orphan*/ * modes; } ;
typedef  TYPE_1__ PPFilterContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 int PP_PICT_TYPE_QP2 ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/ * av_frame_get_qp_table (TYPE_2__*,int*,int*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int const,int const) ; 
 int /*<<< orphan*/  pp_postprocess (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pp_filter_frame(AVFilterLink *inlink, AVFrame *inbuf)
{
    AVFilterContext *ctx = inlink->dst;
    PPFilterContext *pp = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    const int aligned_w = FFALIGN(outlink->w, 8);
    const int aligned_h = FFALIGN(outlink->h, 8);
    AVFrame *outbuf;
    int qstride, qp_type;
    int8_t *qp_table ;

    outbuf = ff_get_video_buffer(outlink, aligned_w, aligned_h);
    if (!outbuf) {
        av_frame_free(&inbuf);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(outbuf, inbuf);
    outbuf->width  = inbuf->width;
    outbuf->height = inbuf->height;
    qp_table = av_frame_get_qp_table(inbuf, &qstride, &qp_type);

    pp_postprocess((const uint8_t **)inbuf->data, inbuf->linesize,
                   outbuf->data,                 outbuf->linesize,
                   aligned_w, outlink->h,
                   qp_table,
                   qstride,
                   pp->modes[pp->mode_id],
                   pp->pp_ctx,
                   outbuf->pict_type | (qp_type ? PP_PICT_TYPE_QP2 : 0));

    av_frame_free(&inbuf);
    return ff_filter_frame(outlink, outbuf);
}