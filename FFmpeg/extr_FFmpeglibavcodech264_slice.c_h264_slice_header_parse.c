#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;

/* Type definitions */
struct TYPE_35__ {scalar_t__ type; scalar_t__ ref_idc; } ;
struct TYPE_30__ {int frame_num; } ;
struct TYPE_29__ {TYPE_2__** sps_list; TYPE_1__** pps_list; } ;
struct TYPE_34__ {TYPE_16__* avctx; TYPE_4__ poc; TYPE_3__ ps; int /*<<< orphan*/  setup_finished; int /*<<< orphan*/  current_slice; TYPE_7__* slice_ctx; } ;
struct TYPE_25__ {scalar_t__* chroma_weight_flag; scalar_t__* luma_weight_flag; scalar_t__ use_weight; } ;
struct TYPE_33__ {int first_mb_addr; int slice_type_fixed; unsigned int slice_type; unsigned int slice_type_nos; size_t pps_id; int frame_num; int picture_structure; int mb_field_decoding_flag; int curr_pic_num; int max_pic_num; unsigned int cabac_init_idc; unsigned int qscale; int deblocking_filter; int slice_alpha_c0_offset; int slice_beta_offset; int /*<<< orphan*/  gb; void** chroma_qp; scalar_t__ last_qscale_diff; scalar_t__ explicit_ref_marking; TYPE_15__ pwt; scalar_t__* ref_count; int /*<<< orphan*/  list_count; void* direct_spatial_mv_pred; void* redundant_pic_count; void** delta_poc; void* delta_poc_bottom; void* poc_lsb; scalar_t__ mb_mbaff; } ;
struct TYPE_32__ {size_t sps_id; int pic_order_present; int weighted_bipred_idc; scalar_t__ deblocking_filter_parameters_present; int /*<<< orphan*/  init_qp; scalar_t__ cabac; scalar_t__ weighted_pred; scalar_t__ redundant_pic_cnt_present; } ;
struct TYPE_31__ {int log2_max_frame_num; int poc_type; int log2_max_poc_lsb; int bit_depth_luma; int /*<<< orphan*/  delta_pic_order_always_zero_flag; int /*<<< orphan*/  direct_8x8_inference_flag; scalar_t__ frame_mbs_only_flag; } ;
struct TYPE_28__ {scalar_t__ data; } ;
struct TYPE_27__ {scalar_t__ data; } ;
struct TYPE_26__ {int err_recognition; } ;
typedef  TYPE_5__ SPS ;
typedef  TYPE_6__ PPS ;
typedef  TYPE_7__ H264SliceContext ;
typedef  TYPE_8__ H264Context ;
typedef  TYPE_9__ H2645NAL ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int AV_PICTURE_TYPE_B ; 
 unsigned int AV_PICTURE_TYPE_I ; 
 unsigned int AV_PICTURE_TYPE_P ; 
 unsigned int AV_PICTURE_TYPE_SI ; 
 unsigned int AV_PICTURE_TYPE_SP ; 
 scalar_t__ H264_NAL_IDR_SLICE ; 
 size_t MAX_PPS_COUNT ; 
 int PICT_FRAME ; 
 int PICT_TOP_FIELD ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_16__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_h264_decode_ref_pic_list_reordering (TYPE_7__*,TYPE_16__*) ; 
 int ff_h264_decode_ref_pic_marking (TYPE_7__*,int /*<<< orphan*/ *,TYPE_9__ const*,TYPE_16__*) ; 
 unsigned int* ff_h264_golomb_to_pict_type ; 
 int ff_h264_parse_ref_count (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,TYPE_6__ const*,unsigned int,int,TYPE_16__*) ; 
 int ff_h264_pred_weight_table (int /*<<< orphan*/ *,TYPE_5__ const*,scalar_t__*,unsigned int,TYPE_15__*,int,TYPE_16__*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_chroma_qp (TYPE_6__ const*,int,unsigned int) ; 
 void* get_se_golomb (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb (int /*<<< orphan*/ *) ; 
 unsigned int get_ue_golomb_31 (int /*<<< orphan*/ *) ; 
 int get_ue_golomb_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h264_slice_header_parse(const H264Context *h, H264SliceContext *sl,
                                   const H2645NAL *nal)
{
    const SPS *sps;
    const PPS *pps;
    int ret;
    unsigned int slice_type, tmp, i;
    int field_pic_flag, bottom_field_flag;
    int first_slice = sl == h->slice_ctx && !h->current_slice;
    int picture_structure;

    if (first_slice)
        av_assert0(!h->setup_finished);

    sl->first_mb_addr = get_ue_golomb_long(&sl->gb);

    slice_type = get_ue_golomb_31(&sl->gb);
    if (slice_type > 9) {
        av_log(h->avctx, AV_LOG_ERROR,
               "slice type %d too large at %d\n",
               slice_type, sl->first_mb_addr);
        return AVERROR_INVALIDDATA;
    }
    if (slice_type > 4) {
        slice_type -= 5;
        sl->slice_type_fixed = 1;
    } else
        sl->slice_type_fixed = 0;

    slice_type         = ff_h264_golomb_to_pict_type[slice_type];
    sl->slice_type     = slice_type;
    sl->slice_type_nos = slice_type & 3;

    if (nal->type  == H264_NAL_IDR_SLICE &&
        sl->slice_type_nos != AV_PICTURE_TYPE_I) {
        av_log(h->avctx, AV_LOG_ERROR, "A non-intra slice in an IDR NAL unit.\n");
        return AVERROR_INVALIDDATA;
    }

    sl->pps_id = get_ue_golomb(&sl->gb);
    if (sl->pps_id >= MAX_PPS_COUNT) {
        av_log(h->avctx, AV_LOG_ERROR, "pps_id %u out of range\n", sl->pps_id);
        return AVERROR_INVALIDDATA;
    }
    if (!h->ps.pps_list[sl->pps_id]) {
        av_log(h->avctx, AV_LOG_ERROR,
               "non-existing PPS %u referenced\n",
               sl->pps_id);
        return AVERROR_INVALIDDATA;
    }
    pps = (const PPS*)h->ps.pps_list[sl->pps_id]->data;

    if (!h->ps.sps_list[pps->sps_id]) {
        av_log(h->avctx, AV_LOG_ERROR,
               "non-existing SPS %u referenced\n", pps->sps_id);
        return AVERROR_INVALIDDATA;
    }
    sps = (const SPS*)h->ps.sps_list[pps->sps_id]->data;

    sl->frame_num = get_bits(&sl->gb, sps->log2_max_frame_num);
    if (!first_slice) {
        if (h->poc.frame_num != sl->frame_num) {
            av_log(h->avctx, AV_LOG_ERROR, "Frame num change from %d to %d\n",
                   h->poc.frame_num, sl->frame_num);
            return AVERROR_INVALIDDATA;
        }
    }

    sl->mb_mbaff       = 0;

    if (sps->frame_mbs_only_flag) {
        picture_structure = PICT_FRAME;
    } else {
        if (!sps->direct_8x8_inference_flag && slice_type == AV_PICTURE_TYPE_B) {
            av_log(h->avctx, AV_LOG_ERROR, "This stream was generated by a broken encoder, invalid 8x8 inference\n");
            return -1;
        }
        field_pic_flag = get_bits1(&sl->gb);
        if (field_pic_flag) {
            bottom_field_flag = get_bits1(&sl->gb);
            picture_structure = PICT_TOP_FIELD + bottom_field_flag;
        } else {
            picture_structure = PICT_FRAME;
        }
    }
    sl->picture_structure      = picture_structure;
    sl->mb_field_decoding_flag = picture_structure != PICT_FRAME;

    if (picture_structure == PICT_FRAME) {
        sl->curr_pic_num = sl->frame_num;
        sl->max_pic_num  = 1 << sps->log2_max_frame_num;
    } else {
        sl->curr_pic_num = 2 * sl->frame_num + 1;
        sl->max_pic_num  = 1 << (sps->log2_max_frame_num + 1);
    }

    if (nal->type == H264_NAL_IDR_SLICE)
        get_ue_golomb_long(&sl->gb); /* idr_pic_id */

    if (sps->poc_type == 0) {
        sl->poc_lsb = get_bits(&sl->gb, sps->log2_max_poc_lsb);

        if (pps->pic_order_present == 1 && picture_structure == PICT_FRAME)
            sl->delta_poc_bottom = get_se_golomb(&sl->gb);
    }

    if (sps->poc_type == 1 && !sps->delta_pic_order_always_zero_flag) {
        sl->delta_poc[0] = get_se_golomb(&sl->gb);

        if (pps->pic_order_present == 1 && picture_structure == PICT_FRAME)
            sl->delta_poc[1] = get_se_golomb(&sl->gb);
    }

    sl->redundant_pic_count = 0;
    if (pps->redundant_pic_cnt_present)
        sl->redundant_pic_count = get_ue_golomb(&sl->gb);

    if (sl->slice_type_nos == AV_PICTURE_TYPE_B)
        sl->direct_spatial_mv_pred = get_bits1(&sl->gb);

    ret = ff_h264_parse_ref_count(&sl->list_count, sl->ref_count,
                                  &sl->gb, pps, sl->slice_type_nos,
                                  picture_structure, h->avctx);
    if (ret < 0)
        return ret;

    if (sl->slice_type_nos != AV_PICTURE_TYPE_I) {
       ret = ff_h264_decode_ref_pic_list_reordering(sl, h->avctx);
       if (ret < 0) {
           sl->ref_count[1] = sl->ref_count[0] = 0;
           return ret;
       }
    }

    sl->pwt.use_weight = 0;
    for (i = 0; i < 2; i++) {
        sl->pwt.luma_weight_flag[i]   = 0;
        sl->pwt.chroma_weight_flag[i] = 0;
    }
    if ((pps->weighted_pred && sl->slice_type_nos == AV_PICTURE_TYPE_P) ||
        (pps->weighted_bipred_idc == 1 &&
         sl->slice_type_nos == AV_PICTURE_TYPE_B)) {
        ret = ff_h264_pred_weight_table(&sl->gb, sps, sl->ref_count,
                                  sl->slice_type_nos, &sl->pwt,
                                  picture_structure, h->avctx);
        if (ret < 0)
            return ret;
    }

    sl->explicit_ref_marking = 0;
    if (nal->ref_idc) {
        ret = ff_h264_decode_ref_pic_marking(sl, &sl->gb, nal, h->avctx);
        if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))
            return AVERROR_INVALIDDATA;
    }

    if (sl->slice_type_nos != AV_PICTURE_TYPE_I && pps->cabac) {
        tmp = get_ue_golomb_31(&sl->gb);
        if (tmp > 2) {
            av_log(h->avctx, AV_LOG_ERROR, "cabac_init_idc %u overflow\n", tmp);
            return AVERROR_INVALIDDATA;
        }
        sl->cabac_init_idc = tmp;
    }

    sl->last_qscale_diff = 0;
    tmp = pps->init_qp + (unsigned)get_se_golomb(&sl->gb);
    if (tmp > 51 + 6 * (sps->bit_depth_luma - 8)) {
        av_log(h->avctx, AV_LOG_ERROR, "QP %u out of range\n", tmp);
        return AVERROR_INVALIDDATA;
    }
    sl->qscale       = tmp;
    sl->chroma_qp[0] = get_chroma_qp(pps, 0, sl->qscale);
    sl->chroma_qp[1] = get_chroma_qp(pps, 1, sl->qscale);
    // FIXME qscale / qp ... stuff
    if (sl->slice_type == AV_PICTURE_TYPE_SP)
        get_bits1(&sl->gb); /* sp_for_switch_flag */
    if (sl->slice_type == AV_PICTURE_TYPE_SP ||
        sl->slice_type == AV_PICTURE_TYPE_SI)
        get_se_golomb(&sl->gb); /* slice_qs_delta */

    sl->deblocking_filter     = 1;
    sl->slice_alpha_c0_offset = 0;
    sl->slice_beta_offset     = 0;
    if (pps->deblocking_filter_parameters_present) {
        tmp = get_ue_golomb_31(&sl->gb);
        if (tmp > 2) {
            av_log(h->avctx, AV_LOG_ERROR,
                   "deblocking_filter_idc %u out of range\n", tmp);
            return AVERROR_INVALIDDATA;
        }
        sl->deblocking_filter = tmp;
        if (sl->deblocking_filter < 2)
            sl->deblocking_filter ^= 1;  // 1<->0

        if (sl->deblocking_filter) {
            int slice_alpha_c0_offset_div2 = get_se_golomb(&sl->gb);
            int slice_beta_offset_div2     = get_se_golomb(&sl->gb);
            if (slice_alpha_c0_offset_div2 >  6 ||
                slice_alpha_c0_offset_div2 < -6 ||
                slice_beta_offset_div2 >  6     ||
                slice_beta_offset_div2 < -6) {
                av_log(h->avctx, AV_LOG_ERROR,
                       "deblocking filter parameters %d %d out of range\n",
                       slice_alpha_c0_offset_div2, slice_beta_offset_div2);
                return AVERROR_INVALIDDATA;
            }
            sl->slice_alpha_c0_offset = slice_alpha_c0_offset_div2 * 2;
            sl->slice_beta_offset     = slice_beta_offset_div2 * 2;
        }
    }

    return 0;
}