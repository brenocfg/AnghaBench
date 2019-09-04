#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_19__ {TYPE_5__** outputs; TYPE_1__* priv; } ;
struct TYPE_18__ {TYPE_6__* dst; } ;
struct TYPE_17__ {int** data; int* linesize; scalar_t__ pict_type; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_16__ {int size; scalar_t__ data; } ;
struct TYPE_15__ {scalar_t__ source; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; int /*<<< orphan*/  dst_y; int /*<<< orphan*/  dst_x; } ;
struct TYPE_14__ {int mv; int mv_type; int frame_type; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; scalar_t__ qp; } ;
typedef  TYPE_1__ CodecViewContext ;
typedef  TYPE_2__ AVMotionVector ;
typedef  TYPE_3__ AVFrameSideData ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_FRAME_DATA_MOTION_VECTORS ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int FRAME_TYPE_B ; 
 int FRAME_TYPE_I ; 
 int FRAME_TYPE_P ; 
 int MV_B_BACK ; 
 int MV_B_FOR ; 
 int MV_P_FOR ; 
 int MV_TYPE_BACK ; 
 int MV_TYPE_FOR ; 
 int /*<<< orphan*/ * av_frame_get_qp_table (TYPE_4__*,int*,int*) ; 
 TYPE_3__* av_frame_get_side_data (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_arrow (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int const) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 int ff_norm_qscale (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    CodecViewContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];

    if (s->qp) {
        int qstride, qp_type;
        int8_t *qp_table = av_frame_get_qp_table(frame, &qstride, &qp_type);

        if (qp_table) {
            int x, y;
            const int w = AV_CEIL_RSHIFT(frame->width,  s->hsub);
            const int h = AV_CEIL_RSHIFT(frame->height, s->vsub);
            uint8_t *pu = frame->data[1];
            uint8_t *pv = frame->data[2];
            const int lzu = frame->linesize[1];
            const int lzv = frame->linesize[2];

            for (y = 0; y < h; y++) {
                for (x = 0; x < w; x++) {
                    const int qp = ff_norm_qscale(qp_table[(y >> 3) * qstride + (x >> 3)], qp_type) * 128/31;
                    pu[x] = pv[x] = qp;
                }
                pu += lzu;
                pv += lzv;
            }
        }
    }

    if (s->mv || s->mv_type) {
        AVFrameSideData *sd = av_frame_get_side_data(frame, AV_FRAME_DATA_MOTION_VECTORS);
        if (sd) {
            int i;
            const AVMotionVector *mvs = (const AVMotionVector *)sd->data;
            const int is_iframe = (s->frame_type & FRAME_TYPE_I) && frame->pict_type == AV_PICTURE_TYPE_I;
            const int is_pframe = (s->frame_type & FRAME_TYPE_P) && frame->pict_type == AV_PICTURE_TYPE_P;
            const int is_bframe = (s->frame_type & FRAME_TYPE_B) && frame->pict_type == AV_PICTURE_TYPE_B;

            for (i = 0; i < sd->size / sizeof(*mvs); i++) {
                const AVMotionVector *mv = &mvs[i];
                const int direction = mv->source > 0;

                if (s->mv_type) {
                    const int is_fp = direction == 0 && (s->mv_type & MV_TYPE_FOR);
                    const int is_bp = direction == 1 && (s->mv_type & MV_TYPE_BACK);

                    if ((!s->frame_type && (is_fp || is_bp)) ||
                        is_iframe && is_fp || is_iframe && is_bp ||
                        is_pframe && is_fp ||
                        is_bframe && is_fp || is_bframe && is_bp)
                        draw_arrow(frame->data[0], mv->dst_x, mv->dst_y, mv->src_x, mv->src_y,
                                   frame->width, frame->height, frame->linesize[0],
                                   100, 0, direction);
                } else if (s->mv)
                    if ((direction == 0 && (s->mv & MV_P_FOR)  && frame->pict_type == AV_PICTURE_TYPE_P) ||
                        (direction == 0 && (s->mv & MV_B_FOR)  && frame->pict_type == AV_PICTURE_TYPE_B) ||
                        (direction == 1 && (s->mv & MV_B_BACK) && frame->pict_type == AV_PICTURE_TYPE_B))
                        draw_arrow(frame->data[0], mv->dst_x, mv->dst_y, mv->src_x, mv->src_y,
                                   frame->width, frame->height, frame->linesize[0],
                                   100, 0, direction);
            }
        }
    }

    return ff_filter_frame(outlink, frame);
}