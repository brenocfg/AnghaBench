#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_33__ {scalar_t__ picture_struct; } ;
struct TYPE_34__ {TYPE_8__ picture_timing; } ;
struct TYPE_32__ {int top_field_first; int interlaced_frame; scalar_t__* buf; } ;
struct TYPE_31__ {scalar_t__ data; } ;
struct TYPE_30__ {TYPE_4__* sps; } ;
struct TYPE_29__ {int ctb_width; int ctb_height; } ;
struct TYPE_28__ {scalar_t__ data; } ;
struct TYPE_27__ {scalar_t__ data; } ;
struct TYPE_26__ {int nb_nals; } ;
struct TYPE_25__ {TYPE_13__* hwaccel; } ;
struct TYPE_24__ {int frame_priv_data_size; } ;
struct TYPE_23__ {TYPE_14__* avctx; TYPE_9__ sei; TYPE_5__ ps; int /*<<< orphan*/  rpl_tab_pool; int /*<<< orphan*/  tab_mvf_pool; TYPE_1__ pkt; TYPE_11__* DPB; } ;
struct TYPE_22__ {int ctb_count; TYPE_10__* hwaccel_priv_buf; scalar_t__ hwaccel_picture_private; TYPE_7__* frame; TYPE_6__* rpl_buf; int /*<<< orphan*/ ** rpl_tab; TYPE_3__* rpl_tab_buf; TYPE_2__* tab_mvf_buf; int /*<<< orphan*/ * tab_mvf; int /*<<< orphan*/  tf; } ;
struct TYPE_21__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  RefPicListTab ;
typedef  int /*<<< orphan*/  MvField ;
typedef  TYPE_11__ HEVCFrame ;
typedef  TYPE_12__ HEVCContext ;
typedef  TYPE_13__ AVHWAccel ;

/* Variables and functions */
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_STRUCTURE_BOTTOM_FIELD ; 
 scalar_t__ AV_PICTURE_STRUCTURE_TOP_FIELD ; 
 int FF_ARRAY_ELEMS (TYPE_11__*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 void* av_buffer_allocz (int) ; 
 void* av_buffer_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_14__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_hevc_unref_frame (TYPE_12__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int ff_thread_get_buffer (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HEVCFrame *alloc_frame(HEVCContext *s)
{
    int i, j, ret;
    for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
        HEVCFrame *frame = &s->DPB[i];
        if (frame->frame->buf[0])
            continue;

        ret = ff_thread_get_buffer(s->avctx, &frame->tf,
                                   AV_GET_BUFFER_FLAG_REF);
        if (ret < 0)
            return NULL;

        frame->rpl_buf = av_buffer_allocz(s->pkt.nb_nals * sizeof(RefPicListTab));
        if (!frame->rpl_buf)
            goto fail;

        frame->tab_mvf_buf = av_buffer_pool_get(s->tab_mvf_pool);
        if (!frame->tab_mvf_buf)
            goto fail;
        frame->tab_mvf = (MvField *)frame->tab_mvf_buf->data;

        frame->rpl_tab_buf = av_buffer_pool_get(s->rpl_tab_pool);
        if (!frame->rpl_tab_buf)
            goto fail;
        frame->rpl_tab   = (RefPicListTab **)frame->rpl_tab_buf->data;
        frame->ctb_count = s->ps.sps->ctb_width * s->ps.sps->ctb_height;
        for (j = 0; j < frame->ctb_count; j++)
            frame->rpl_tab[j] = (RefPicListTab *)frame->rpl_buf->data;

        frame->frame->top_field_first  = s->sei.picture_timing.picture_struct == AV_PICTURE_STRUCTURE_TOP_FIELD;
        frame->frame->interlaced_frame = (s->sei.picture_timing.picture_struct == AV_PICTURE_STRUCTURE_TOP_FIELD) || (s->sei.picture_timing.picture_struct == AV_PICTURE_STRUCTURE_BOTTOM_FIELD);

        if (s->avctx->hwaccel) {
            const AVHWAccel *hwaccel = s->avctx->hwaccel;
            av_assert0(!frame->hwaccel_picture_private);
            if (hwaccel->frame_priv_data_size) {
                frame->hwaccel_priv_buf = av_buffer_allocz(hwaccel->frame_priv_data_size);
                if (!frame->hwaccel_priv_buf)
                    goto fail;
                frame->hwaccel_picture_private = frame->hwaccel_priv_buf->data;
            }
        }

        return frame;
fail:
        ff_hevc_unref_frame(s, frame, ~0);
        return NULL;
    }
    av_log(s->avctx, AV_LOG_ERROR, "Error allocating frame, DPB full.\n");
    return NULL;
}