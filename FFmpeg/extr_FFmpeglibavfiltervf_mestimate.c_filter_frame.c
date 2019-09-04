#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_24__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_23__ {TYPE_7__* dst; } ;
struct TYPE_22__ {scalar_t__ pts; int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {void* pred_y; void* pred_x; TYPE_2__* preds; int /*<<< orphan*/  mb_size; int /*<<< orphan*/  data_ref; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data_cur; } ;
struct TYPE_19__ {int nb; void*** mvs; } ;
struct TYPE_18__ {int**** mv_table; int b_count; scalar_t__ method; int b_height; int b_width; int log2_mb_size; int /*<<< orphan*/  mb_size; TYPE_5__* prev; TYPE_5__* next; TYPE_5__* cur; TYPE_3__ me_ctx; } ;
typedef  TYPE_1__ MEContext ;
typedef  int /*<<< orphan*/  AVMotionVector ;
typedef  TYPE_2__ AVMotionEstPredictor ;
typedef  TYPE_3__ AVMotionEstContext ;
typedef  TYPE_4__ AVFrameSideData ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PRED (TYPE_2__,int,int) ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_FRAME_DATA_MOTION_VECTORS ; 
 scalar_t__ AV_ME_METHOD_DS ; 
 scalar_t__ AV_ME_METHOD_EPZS ; 
 scalar_t__ AV_ME_METHOD_ESA ; 
 scalar_t__ AV_ME_METHOD_FSS ; 
 scalar_t__ AV_ME_METHOD_HEXBS ; 
 scalar_t__ AV_ME_METHOD_NTSS ; 
 scalar_t__ AV_ME_METHOD_TDLS ; 
 scalar_t__ AV_ME_METHOD_TSS ; 
 scalar_t__ AV_ME_METHOD_UMH ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEARCH_MV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mv_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int const,int,int,int) ; 
 void* av_frame_clone (TYPE_5__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 TYPE_4__* av_frame_new_side_data (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  esa ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ff_me_search_epzs (TYPE_3__*,int const,int const,int*) ; 
 int /*<<< orphan*/  ff_me_search_umh (TYPE_3__*,int const,int const,int*) ; 
 int /*<<< orphan*/  fss ; 
 int /*<<< orphan*/  hexbs ; 
 void* memcpy (int***,int***,int) ; 
 void* mid_pred (void*,void*,void*) ; 
 int /*<<< orphan*/  ntss ; 
 int /*<<< orphan*/  tdls ; 
 int /*<<< orphan*/  tss ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    AVFilterContext *ctx = inlink->dst;
    MEContext *s = ctx->priv;
    AVMotionEstContext *me_ctx = &s->me_ctx;
    AVFrameSideData *sd;
    AVFrame *out;
    int mb_x, mb_y, dir;
    int32_t mv_count = 0;
    int ret;

    if (frame->pts == AV_NOPTS_VALUE) {
        ret = ff_filter_frame(ctx->outputs[0], frame);
        return ret;
    }

    av_frame_free(&s->prev);
    s->prev = s->cur;
    s->cur  = s->next;
    s->next = frame;

    s->mv_table[2] = memcpy(s->mv_table[2], s->mv_table[1], sizeof(*s->mv_table[1]) * s->b_count);
    s->mv_table[1] = memcpy(s->mv_table[1], s->mv_table[0], sizeof(*s->mv_table[0]) * s->b_count);

    if (!s->cur) {
        s->cur = av_frame_clone(frame);
        if (!s->cur)
            return AVERROR(ENOMEM);
    }

    if (!s->prev)
        return 0;

    out = av_frame_clone(s->cur);
    if (!out)
        return AVERROR(ENOMEM);

    sd = av_frame_new_side_data(out, AV_FRAME_DATA_MOTION_VECTORS, 2 * s->b_count * sizeof(AVMotionVector));
    if (!sd) {
        av_frame_free(&out);
        return AVERROR(ENOMEM);
    }

    me_ctx->data_cur = s->cur->data[0];
    me_ctx->linesize = s->cur->linesize[0];

    for (dir = 0; dir < 2; dir++) {
        me_ctx->data_ref = (dir ? s->next : s->prev)->data[0];

        if (s->method == AV_ME_METHOD_DS)
            SEARCH_MV(ds);
        else if (s->method == AV_ME_METHOD_ESA)
            SEARCH_MV(esa);
        else if (s->method == AV_ME_METHOD_FSS)
            SEARCH_MV(fss);
        else if (s->method == AV_ME_METHOD_NTSS)
            SEARCH_MV(ntss);
        else if (s->method == AV_ME_METHOD_TDLS)
            SEARCH_MV(tdls);
        else if (s->method == AV_ME_METHOD_TSS)
            SEARCH_MV(tss);
        else if (s->method == AV_ME_METHOD_HEXBS)
            SEARCH_MV(hexbs);
        else if (s->method == AV_ME_METHOD_UMH) {
            for (mb_y = 0; mb_y < s->b_height; mb_y++)
                for (mb_x = 0; mb_x < s->b_width; mb_x++) {
                    const int mb_i = mb_x + mb_y * s->b_width;
                    const int x_mb = mb_x << s->log2_mb_size;
                    const int y_mb = mb_y << s->log2_mb_size;
                    int mv[2] = {x_mb, y_mb};

                    AVMotionEstPredictor *preds = me_ctx->preds;
                    preds[0].nb = 0;

                    ADD_PRED(preds[0], 0, 0);

                    //left mb in current frame
                    if (mb_x > 0)
                        ADD_PRED(preds[0], s->mv_table[0][mb_i - 1][dir][0], s->mv_table[0][mb_i - 1][dir][1]);

                    if (mb_y > 0) {
                        //top mb in current frame
                        ADD_PRED(preds[0], s->mv_table[0][mb_i - s->b_width][dir][0], s->mv_table[0][mb_i - s->b_width][dir][1]);

                        //top-right mb in current frame
                        if (mb_x + 1 < s->b_width)
                            ADD_PRED(preds[0], s->mv_table[0][mb_i - s->b_width + 1][dir][0], s->mv_table[0][mb_i - s->b_width + 1][dir][1]);
                        //top-left mb in current frame
                        else if (mb_x > 0)
                            ADD_PRED(preds[0], s->mv_table[0][mb_i - s->b_width - 1][dir][0], s->mv_table[0][mb_i - s->b_width - 1][dir][1]);
                    }

                    //median predictor
                    if (preds[0].nb == 4) {
                        me_ctx->pred_x = mid_pred(preds[0].mvs[1][0], preds[0].mvs[2][0], preds[0].mvs[3][0]);
                        me_ctx->pred_y = mid_pred(preds[0].mvs[1][1], preds[0].mvs[2][1], preds[0].mvs[3][1]);
                    } else if (preds[0].nb == 3) {
                        me_ctx->pred_x = mid_pred(0, preds[0].mvs[1][0], preds[0].mvs[2][0]);
                        me_ctx->pred_y = mid_pred(0, preds[0].mvs[1][1], preds[0].mvs[2][1]);
                    } else if (preds[0].nb == 2) {
                        me_ctx->pred_x = preds[0].mvs[1][0];
                        me_ctx->pred_y = preds[0].mvs[1][1];
                    } else {
                        me_ctx->pred_x = 0;
                        me_ctx->pred_y = 0;
                    }

                    ff_me_search_umh(me_ctx, x_mb, y_mb, mv);

                    s->mv_table[0][mb_i][dir][0] = mv[0] - x_mb;
                    s->mv_table[0][mb_i][dir][1] = mv[1] - y_mb;
                    add_mv_data(((AVMotionVector *) sd->data) + mv_count++, me_ctx->mb_size, x_mb, y_mb, mv[0], mv[1], dir);
                }

        } else if (s->method == AV_ME_METHOD_EPZS) {

            for (mb_y = 0; mb_y < s->b_height; mb_y++)
                for (mb_x = 0; mb_x < s->b_width; mb_x++) {
                    const int mb_i = mb_x + mb_y * s->b_width;
                    const int x_mb = mb_x << s->log2_mb_size;
                    const int y_mb = mb_y << s->log2_mb_size;
                    int mv[2] = {x_mb, y_mb};

                    AVMotionEstPredictor *preds = me_ctx->preds;
                    preds[0].nb = 0;
                    preds[1].nb = 0;

                    ADD_PRED(preds[0], 0, 0);

                    //left mb in current frame
                    if (mb_x > 0)
                        ADD_PRED(preds[0], s->mv_table[0][mb_i - 1][dir][0], s->mv_table[0][mb_i - 1][dir][1]);

                    //top mb in current frame
                    if (mb_y > 0)
                        ADD_PRED(preds[0], s->mv_table[0][mb_i - s->b_width][dir][0], s->mv_table[0][mb_i - s->b_width][dir][1]);

                    //top-right mb in current frame
                    if (mb_y > 0 && mb_x + 1 < s->b_width)
                        ADD_PRED(preds[0], s->mv_table[0][mb_i - s->b_width + 1][dir][0], s->mv_table[0][mb_i - s->b_width + 1][dir][1]);

                    //median predictor
                    if (preds[0].nb == 4) {
                        me_ctx->pred_x = mid_pred(preds[0].mvs[1][0], preds[0].mvs[2][0], preds[0].mvs[3][0]);
                        me_ctx->pred_y = mid_pred(preds[0].mvs[1][1], preds[0].mvs[2][1], preds[0].mvs[3][1]);
                    } else if (preds[0].nb == 3) {
                        me_ctx->pred_x = mid_pred(0, preds[0].mvs[1][0], preds[0].mvs[2][0]);
                        me_ctx->pred_y = mid_pred(0, preds[0].mvs[1][1], preds[0].mvs[2][1]);
                    } else if (preds[0].nb == 2) {
                        me_ctx->pred_x = preds[0].mvs[1][0];
                        me_ctx->pred_y = preds[0].mvs[1][1];
                    } else {
                        me_ctx->pred_x = 0;
                        me_ctx->pred_y = 0;
                    }

                    //collocated mb in prev frame
                    ADD_PRED(preds[0], s->mv_table[1][mb_i][dir][0], s->mv_table[1][mb_i][dir][1]);

                    //accelerator motion vector of collocated block in prev frame
                    ADD_PRED(preds[1], s->mv_table[1][mb_i][dir][0] + (s->mv_table[1][mb_i][dir][0] - s->mv_table[2][mb_i][dir][0]),
                                       s->mv_table[1][mb_i][dir][1] + (s->mv_table[1][mb_i][dir][1] - s->mv_table[2][mb_i][dir][1]));

                    //left mb in prev frame
                    if (mb_x > 0)
                        ADD_PRED(preds[1], s->mv_table[1][mb_i - 1][dir][0], s->mv_table[1][mb_i - 1][dir][1]);

                    //top mb in prev frame
                    if (mb_y > 0)
                        ADD_PRED(preds[1], s->mv_table[1][mb_i - s->b_width][dir][0], s->mv_table[1][mb_i - s->b_width][dir][1]);

                    //right mb in prev frame
                    if (mb_x + 1 < s->b_width)
                        ADD_PRED(preds[1], s->mv_table[1][mb_i + 1][dir][0], s->mv_table[1][mb_i + 1][dir][1]);

                    //bottom mb in prev frame
                    if (mb_y + 1 < s->b_height)
                        ADD_PRED(preds[1], s->mv_table[1][mb_i + s->b_width][dir][0], s->mv_table[1][mb_i + s->b_width][dir][1]);

                    ff_me_search_epzs(me_ctx, x_mb, y_mb, mv);

                    s->mv_table[0][mb_i][dir][0] = mv[0] - x_mb;
                    s->mv_table[0][mb_i][dir][1] = mv[1] - y_mb;
                    add_mv_data(((AVMotionVector *) sd->data) + mv_count++, s->mb_size, x_mb, y_mb, mv[0], mv[1], dir);
                }
        }
    }

    return ff_filter_frame(ctx->outputs[0], out);
}