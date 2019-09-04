#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_18__ ;
typedef  struct TYPE_23__   TYPE_17__ ;
typedef  struct TYPE_22__   TYPE_13__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ x264_build; } ;
struct TYPE_29__ {int /*<<< orphan*/  recovery_frame_cnt; } ;
struct TYPE_30__ {TYPE_1__ unregistered; TYPE_5__ recovery_point; } ;
struct TYPE_27__ {TYPE_2__* sps; } ;
struct TYPE_28__ {int /*<<< orphan*/  frame_num; } ;
struct TYPE_33__ {int pixel_shift; scalar_t__ picture_structure; int nb_slice_ctx; int* block_offset; int mb_aff_frame; scalar_t__ x264_build; TYPE_8__* cur_pic_ptr; TYPE_6__ sei; TYPE_3__ ps; scalar_t__ postpone_filter; int /*<<< orphan*/ * next_output_pic; TYPE_7__* slice_ctx; scalar_t__ enable_er; int /*<<< orphan*/  cur_pic; TYPE_13__* avctx; int /*<<< orphan*/  frame_recovered; int /*<<< orphan*/  crop_bottom; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  crop_right; int /*<<< orphan*/  crop_left; TYPE_4__ poc; int /*<<< orphan*/  coded_picture_number; scalar_t__ droppable; TYPE_8__* DPB; } ;
struct TYPE_32__ {scalar_t__ reference; int field_picture; scalar_t__ long_ref; int /*<<< orphan*/ * field_poc; TYPE_18__* f; int /*<<< orphan*/  sei_recovery_frame_cnt; scalar_t__ invalid_gap; scalar_t__ recovered; scalar_t__ mmco_reset; int /*<<< orphan*/  frame_num; } ;
struct TYPE_23__ {int /*<<< orphan*/  next_pic; int /*<<< orphan*/  last_pic; int /*<<< orphan*/  cur_pic; } ;
struct TYPE_31__ {int linesize; int uvlinesize; TYPE_17__ er; int /*<<< orphan*/  slice_type; } ;
struct TYPE_26__ {scalar_t__ mb_aff; int /*<<< orphan*/  bit_depth_chroma; int /*<<< orphan*/  bit_depth_luma; } ;
struct TYPE_24__ {int* linesize; int /*<<< orphan*/  crop_bottom; int /*<<< orphan*/  crop_top; int /*<<< orphan*/  crop_right; int /*<<< orphan*/  crop_left; int /*<<< orphan*/  pict_type; scalar_t__ key_frame; scalar_t__ coded_picture_number; } ;
struct TYPE_22__ {int /*<<< orphan*/  hwaccel; } ;
typedef  TYPE_8__ H264Picture ;
typedef  TYPE_9__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ CONFIG_ERROR_RESILIENCE ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ PICT_FRAME ; 
 int alloc_picture (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_log (TYPE_13__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_color_frame (TYPE_18__*,int*) ; 
 int /*<<< orphan*/  ff_er_frame_start (TYPE_17__*) ; 
 int ff_h264_ref_picture (TYPE_9__*,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  ff_h264_set_erpic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h264_unref_picture (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_thread_can_start_frame (TYPE_13__*) ; 
 int find_unused_picture (TYPE_9__*) ; 
 int /*<<< orphan*/  release_unused_pictures (TYPE_9__*,int) ; 
 int* scan8 ; 

__attribute__((used)) static int h264_frame_start(H264Context *h)
{
    H264Picture *pic;
    int i, ret;
    const int pixel_shift = h->pixel_shift;
    int c[4] = {
        1<<(h->ps.sps->bit_depth_luma-1),
        1<<(h->ps.sps->bit_depth_chroma-1),
        1<<(h->ps.sps->bit_depth_chroma-1),
        -1
    };

    if (!ff_thread_can_start_frame(h->avctx)) {
        av_log(h->avctx, AV_LOG_ERROR, "Attempt to start a frame outside SETUP state\n");
        return -1;
    }

    release_unused_pictures(h, 1);
    h->cur_pic_ptr = NULL;

    i = find_unused_picture(h);
    if (i < 0) {
        av_log(h->avctx, AV_LOG_ERROR, "no frame buffer available\n");
        return i;
    }
    pic = &h->DPB[i];

    pic->reference              = h->droppable ? 0 : h->picture_structure;
    pic->f->coded_picture_number = h->coded_picture_number++;
    pic->field_picture          = h->picture_structure != PICT_FRAME;
    pic->frame_num               = h->poc.frame_num;
    /*
     * Zero key_frame here; IDR markings per slice in frame or fields are ORed
     * in later.
     * See decode_nal_units().
     */
    pic->f->key_frame = 0;
    pic->mmco_reset  = 0;
    pic->recovered   = 0;
    pic->invalid_gap = 0;
    pic->sei_recovery_frame_cnt = h->sei.recovery_point.recovery_frame_cnt;

    pic->f->pict_type = h->slice_ctx[0].slice_type;

    pic->f->crop_left   = h->crop_left;
    pic->f->crop_right  = h->crop_right;
    pic->f->crop_top    = h->crop_top;
    pic->f->crop_bottom = h->crop_bottom;

    if ((ret = alloc_picture(h, pic)) < 0)
        return ret;
    if(!h->frame_recovered && !h->avctx->hwaccel)
        ff_color_frame(pic->f, c);

    h->cur_pic_ptr = pic;
    ff_h264_unref_picture(h, &h->cur_pic);
    if (CONFIG_ERROR_RESILIENCE) {
        ff_h264_set_erpic(&h->slice_ctx[0].er.cur_pic, NULL);
    }

    if ((ret = ff_h264_ref_picture(h, &h->cur_pic, h->cur_pic_ptr)) < 0)
        return ret;

    for (i = 0; i < h->nb_slice_ctx; i++) {
        h->slice_ctx[i].linesize   = h->cur_pic_ptr->f->linesize[0];
        h->slice_ctx[i].uvlinesize = h->cur_pic_ptr->f->linesize[1];
    }

    if (CONFIG_ERROR_RESILIENCE && h->enable_er) {
        ff_er_frame_start(&h->slice_ctx[0].er);
        ff_h264_set_erpic(&h->slice_ctx[0].er.last_pic, NULL);
        ff_h264_set_erpic(&h->slice_ctx[0].er.next_pic, NULL);
    }

    for (i = 0; i < 16; i++) {
        h->block_offset[i]           = (4 * ((scan8[i] - scan8[0]) & 7) << pixel_shift) + 4 * pic->f->linesize[0] * ((scan8[i] - scan8[0]) >> 3);
        h->block_offset[48 + i]      = (4 * ((scan8[i] - scan8[0]) & 7) << pixel_shift) + 8 * pic->f->linesize[0] * ((scan8[i] - scan8[0]) >> 3);
    }
    for (i = 0; i < 16; i++) {
        h->block_offset[16 + i]      =
        h->block_offset[32 + i]      = (4 * ((scan8[i] - scan8[0]) & 7) << pixel_shift) + 4 * pic->f->linesize[1] * ((scan8[i] - scan8[0]) >> 3);
        h->block_offset[48 + 16 + i] =
        h->block_offset[48 + 32 + i] = (4 * ((scan8[i] - scan8[0]) & 7) << pixel_shift) + 8 * pic->f->linesize[1] * ((scan8[i] - scan8[0]) >> 3);
    }

    /* We mark the current picture as non-reference after allocating it, so
     * that if we break out due to an error it can be released automatically
     * in the next ff_mpv_frame_start().
     */
    h->cur_pic_ptr->reference = 0;

    h->cur_pic_ptr->field_poc[0] = h->cur_pic_ptr->field_poc[1] = INT_MAX;

    h->next_output_pic = NULL;

    h->postpone_filter = 0;

    h->mb_aff_frame = h->ps.sps->mb_aff && (h->picture_structure == PICT_FRAME);

    if (h->sei.unregistered.x264_build >= 0)
        h->x264_build = h->sei.unregistered.x264_build;

    assert(h->cur_pic_ptr->long_ref == 0);

    return 0;
}