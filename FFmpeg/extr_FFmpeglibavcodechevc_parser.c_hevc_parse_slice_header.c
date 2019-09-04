#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_19__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_17__ ;
typedef  struct TYPE_33__   TYPE_16__ ;
typedef  struct TYPE_32__   TYPE_15__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {size_t pps_id; int slice_segment_addr; size_t slice_type; void* pic_order_cnt_lsb; void* colour_plane_id; void* pic_output_flag; void* dependent_slice_segment_flag; void* first_slice_in_pic_flag; void* no_output_of_prior_pics_flag; } ;
struct TYPE_44__ {scalar_t__ data; } ;
struct TYPE_43__ {scalar_t__ data; } ;
struct TYPE_42__ {int /*<<< orphan*/  picture_struct; } ;
struct TYPE_41__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_40__ {int vui_num_units_in_tick; int vui_time_scale; scalar_t__ vui_timing_info_present_flag; } ;
struct TYPE_38__ {int /*<<< orphan*/  level_idc; int /*<<< orphan*/  profile_idc; } ;
struct TYPE_39__ {TYPE_2__ general_ptl; } ;
struct TYPE_37__ {scalar_t__ data; } ;
struct TYPE_36__ {TYPE_5__ framerate; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
struct TYPE_35__ {int key_frame; scalar_t__ output_picture_number; int /*<<< orphan*/  pict_type; int /*<<< orphan*/  format; scalar_t__ height; scalar_t__ width; scalar_t__ coded_height; scalar_t__ coded_width; int /*<<< orphan*/  field_order; int /*<<< orphan*/  picture_structure; TYPE_14__* priv_data; } ;
struct TYPE_34__ {scalar_t__ temporal_id; int /*<<< orphan*/  type; int /*<<< orphan*/  gb; } ;
struct TYPE_33__ {size_t sps_id; int num_extra_slice_header_bits; scalar_t__ output_flag_present_flag; scalar_t__ dependent_slice_segments_enabled_flag; } ;
struct TYPE_32__ {TYPE_12__* sps; TYPE_16__* pps; TYPE_11__* vps; TYPE_1__** vps_list; TYPE_8__** sps_list; TYPE_7__** pps_list; } ;
struct TYPE_30__ {TYPE_6__ picture_timing; } ;
struct TYPE_31__ {scalar_t__ poc; scalar_t__ pocTid0; TYPE_9__ sh; TYPE_13__ sei; TYPE_15__ ps; } ;
struct TYPE_27__ {scalar_t__ bottom_offset; scalar_t__ top_offset; scalar_t__ right_offset; scalar_t__ left_offset; } ;
struct TYPE_29__ {size_t vps_id; int ctb_width; int ctb_height; int log2_max_poc_lsb; scalar_t__ separate_colour_plane_flag; TYPE_4__ vui; TYPE_3__ ptl; int /*<<< orphan*/  pix_fmt; scalar_t__ height; scalar_t__ width; TYPE_10__ output_window; } ;
struct TYPE_28__ {int vps_num_units_in_tick; int vps_time_scale; scalar_t__ vps_timing_info_present_flag; } ;
typedef  TYPE_9__ SliceHeader ;
typedef  TYPE_10__ HEVCWindow ;
typedef  TYPE_11__ HEVCVPS ;
typedef  TYPE_12__ HEVCSPS ;
typedef  TYPE_13__ HEVCSEI ;
typedef  TYPE_14__ HEVCParserContext ;
typedef  TYPE_15__ HEVCParamSets ;
typedef  TYPE_16__ HEVCPPS ;
typedef  TYPE_17__ H2645NAL ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_18__ AVCodecParserContext ;
typedef  TYPE_19__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 size_t HEVC_MAX_PPS_COUNT ; 
 size_t HEVC_MAX_SPS_COUNT ; 
 int /*<<< orphan*/  HEVC_NAL_RADL_N ; 
 int /*<<< orphan*/  HEVC_NAL_RADL_R ; 
 int /*<<< orphan*/  HEVC_NAL_RASL_N ; 
 int /*<<< orphan*/  HEVC_NAL_RASL_R ; 
 int /*<<< orphan*/  HEVC_NAL_STSA_N ; 
 int /*<<< orphan*/  HEVC_NAL_TRAIL_N ; 
 int /*<<< orphan*/  HEVC_NAL_TSA_N ; 
 size_t HEVC_SLICE_B ; 
 size_t HEVC_SLICE_I ; 
 size_t HEVC_SLICE_P ; 
 int /*<<< orphan*/  IS_IDR_NAL (TYPE_17__*) ; 
 scalar_t__ IS_IRAP_NAL (TYPE_17__*) ; 
 int av_ceil_log2_c (int) ; 
 int /*<<< orphan*/  av_log (TYPE_19__*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ ff_hevc_compute_poc (TYPE_12__*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bitsz (int /*<<< orphan*/ *,int) ; 
 void* get_ue_golomb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hevc_parse_slice_header(AVCodecParserContext *s, H2645NAL *nal,
                                   AVCodecContext *avctx)
{
    HEVCParserContext *ctx = s->priv_data;
    HEVCParamSets *ps = &ctx->ps;
    HEVCSEI *sei = &ctx->sei;
    SliceHeader *sh = &ctx->sh;
    GetBitContext *gb = &nal->gb;
    const HEVCWindow *ow;
    int i, num = 0, den = 0;

    sh->first_slice_in_pic_flag = get_bits1(gb);
    s->picture_structure = sei->picture_timing.picture_struct;
    s->field_order = sei->picture_timing.picture_struct;

    if (IS_IRAP_NAL(nal)) {
        s->key_frame = 1;
        sh->no_output_of_prior_pics_flag = get_bits1(gb);
    }

    sh->pps_id = get_ue_golomb(gb);
    if (sh->pps_id >= HEVC_MAX_PPS_COUNT || !ps->pps_list[sh->pps_id]) {
        av_log(avctx, AV_LOG_ERROR, "PPS id out of range: %d\n", sh->pps_id);
        return AVERROR_INVALIDDATA;
    }
    ps->pps = (HEVCPPS*)ps->pps_list[sh->pps_id]->data;

    if (ps->pps->sps_id >= HEVC_MAX_SPS_COUNT || !ps->sps_list[ps->pps->sps_id]) {
        av_log(avctx, AV_LOG_ERROR, "SPS id out of range: %d\n", ps->pps->sps_id);
        return AVERROR_INVALIDDATA;
    }
    if (ps->sps != (HEVCSPS*)ps->sps_list[ps->pps->sps_id]->data) {
        ps->sps = (HEVCSPS*)ps->sps_list[ps->pps->sps_id]->data;
        ps->vps = (HEVCVPS*)ps->vps_list[ps->sps->vps_id]->data;
    }
    ow  = &ps->sps->output_window;

    s->coded_width  = ps->sps->width;
    s->coded_height = ps->sps->height;
    s->width        = ps->sps->width  - ow->left_offset - ow->right_offset;
    s->height       = ps->sps->height - ow->top_offset  - ow->bottom_offset;
    s->format       = ps->sps->pix_fmt;
    avctx->profile  = ps->sps->ptl.general_ptl.profile_idc;
    avctx->level    = ps->sps->ptl.general_ptl.level_idc;

    if (ps->vps->vps_timing_info_present_flag) {
        num = ps->vps->vps_num_units_in_tick;
        den = ps->vps->vps_time_scale;
    } else if (ps->sps->vui.vui_timing_info_present_flag) {
        num = ps->sps->vui.vui_num_units_in_tick;
        den = ps->sps->vui.vui_time_scale;
    }

    if (num != 0 && den != 0)
        av_reduce(&avctx->framerate.den, &avctx->framerate.num,
                  num, den, 1 << 30);

    if (!sh->first_slice_in_pic_flag) {
        int slice_address_length;

        if (ps->pps->dependent_slice_segments_enabled_flag)
            sh->dependent_slice_segment_flag = get_bits1(gb);
        else
            sh->dependent_slice_segment_flag = 0;

        slice_address_length = av_ceil_log2_c(ps->sps->ctb_width *
                                              ps->sps->ctb_height);
        sh->slice_segment_addr = get_bitsz(gb, slice_address_length);
        if (sh->slice_segment_addr >= ps->sps->ctb_width * ps->sps->ctb_height) {
            av_log(avctx, AV_LOG_ERROR, "Invalid slice segment address: %u.\n",
                   sh->slice_segment_addr);
            return AVERROR_INVALIDDATA;
        }
    } else
        sh->dependent_slice_segment_flag = 0;

    if (sh->dependent_slice_segment_flag)
        return 0; /* break; */

    for (i = 0; i < ps->pps->num_extra_slice_header_bits; i++)
        skip_bits(gb, 1); // slice_reserved_undetermined_flag[]

    sh->slice_type = get_ue_golomb(gb);
    if (!(sh->slice_type == HEVC_SLICE_I || sh->slice_type == HEVC_SLICE_P ||
          sh->slice_type == HEVC_SLICE_B)) {
        av_log(avctx, AV_LOG_ERROR, "Unknown slice type: %d.\n",
               sh->slice_type);
        return AVERROR_INVALIDDATA;
    }
    s->pict_type = sh->slice_type == HEVC_SLICE_B ? AV_PICTURE_TYPE_B :
                   sh->slice_type == HEVC_SLICE_P ? AV_PICTURE_TYPE_P :
                                               AV_PICTURE_TYPE_I;

    if (ps->pps->output_flag_present_flag)
        sh->pic_output_flag = get_bits1(gb);

    if (ps->sps->separate_colour_plane_flag)
        sh->colour_plane_id = get_bits(gb, 2);

    if (!IS_IDR_NAL(nal)) {
        sh->pic_order_cnt_lsb = get_bits(gb, ps->sps->log2_max_poc_lsb);
        s->output_picture_number = ctx->poc = ff_hevc_compute_poc(ps->sps, ctx->pocTid0, sh->pic_order_cnt_lsb, nal->type);
    } else
        s->output_picture_number = ctx->poc = 0;

    if (nal->temporal_id == 0 &&
        nal->type != HEVC_NAL_TRAIL_N &&
        nal->type != HEVC_NAL_TSA_N &&
        nal->type != HEVC_NAL_STSA_N &&
        nal->type != HEVC_NAL_RADL_N &&
        nal->type != HEVC_NAL_RASL_N &&
        nal->type != HEVC_NAL_RADL_R &&
        nal->type != HEVC_NAL_RASL_R)
        ctx->pocTid0 = ctx->poc;

    return 1; /* no need to evaluate the rest */
}