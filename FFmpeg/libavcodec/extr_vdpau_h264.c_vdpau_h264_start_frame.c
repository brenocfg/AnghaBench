#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  separate_colour_plane_flag; int /*<<< orphan*/  qpprime_y_zero_transform_bypass_flag; } ;
struct TYPE_18__ {int is_reference; int field_pic_flag; int bottom_field_flag; int mb_adaptive_frame_field_flag; int log2_max_pic_order_cnt_lsb_minus4; int /*<<< orphan*/ * scaling_lists_8x8; int /*<<< orphan*/  scaling_lists_4x4; int /*<<< orphan*/  redundant_pic_cnt_present_flag; int /*<<< orphan*/  deblocking_filter_control_present_flag; int /*<<< orphan*/  pic_order_present_flag; int /*<<< orphan*/  entropy_coding_mode_flag; int /*<<< orphan*/  direct_8x8_inference_flag; int /*<<< orphan*/  delta_pic_order_always_zero_flag; scalar_t__ pic_order_cnt_type; scalar_t__ log2_max_frame_num_minus4; scalar_t__ num_ref_idx_l1_active_minus1; scalar_t__ num_ref_idx_l0_active_minus1; scalar_t__ pic_init_qp_minus26; int /*<<< orphan*/  second_chroma_qp_index_offset; int /*<<< orphan*/  chroma_qp_index_offset; int /*<<< orphan*/  transform_8x8_mode_flag; int /*<<< orphan*/  frame_mbs_only_flag; int /*<<< orphan*/  weighted_bipred_idc; int /*<<< orphan*/  weighted_pred_flag; int /*<<< orphan*/  constrained_intra_pred_flag; int /*<<< orphan*/  num_ref_frames; int /*<<< orphan*/  frame_num; void** field_order_cnt; scalar_t__ slice_count; } ;
struct TYPE_15__ {TYPE_4__ h264_predictive; TYPE_5__ h264; } ;
struct vdpau_picture_context {TYPE_2__ info; } ;
typedef  TYPE_4__ VdpPictureInfoH264Predictive ;
typedef  TYPE_5__ VdpPictureInfoH264 ;
struct TYPE_16__ {int /*<<< orphan*/  frame_num; } ;
struct TYPE_14__ {TYPE_6__* sps; TYPE_7__* pps; } ;
struct TYPE_22__ {scalar_t__ nal_ref_idc; scalar_t__ picture_structure; TYPE_3__ poc; TYPE_8__* cur_pic_ptr; TYPE_1__ ps; } ;
struct TYPE_21__ {int /*<<< orphan*/ * field_poc; struct vdpau_picture_context* hwaccel_picture_private; } ;
struct TYPE_20__ {int /*<<< orphan*/ * scaling_matrix8; int /*<<< orphan*/  scaling_matrix4; int /*<<< orphan*/  redundant_pic_cnt_present; int /*<<< orphan*/  deblocking_filter_parameters_present; int /*<<< orphan*/  pic_order_present; int /*<<< orphan*/  cabac; scalar_t__* ref_count; scalar_t__ init_qp; int /*<<< orphan*/ * chroma_qp_index_offset; int /*<<< orphan*/  transform_8x8_mode; int /*<<< orphan*/  weighted_bipred_idc; int /*<<< orphan*/  weighted_pred; int /*<<< orphan*/  constrained_intra_pred; } ;
struct TYPE_19__ {int log2_max_poc_lsb; int /*<<< orphan*/  residual_color_transform_flag; int /*<<< orphan*/  transform_bypass; int /*<<< orphan*/  direct_8x8_inference_flag; int /*<<< orphan*/  delta_pic_order_always_zero_flag; scalar_t__ poc_type; scalar_t__ log2_max_frame_num; int /*<<< orphan*/  frame_mbs_only_flag; scalar_t__ mb_aff; int /*<<< orphan*/  ref_frame_count; } ;
struct TYPE_13__ {TYPE_9__* priv_data; } ;
typedef  TYPE_6__ SPS ;
typedef  TYPE_7__ PPS ;
typedef  TYPE_8__ H264Picture ;
typedef  TYPE_9__ H264Context ;
typedef  TYPE_10__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ PICT_BOTTOM_FIELD ; 
 scalar_t__ PICT_FRAME ; 
 int ff_vdpau_common_start_frame (struct vdpau_picture_context*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* h264_foc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdpau_h264_set_reference_frames (TYPE_10__*) ; 

__attribute__((used)) static int vdpau_h264_start_frame(AVCodecContext *avctx,
                                  const uint8_t *buffer, uint32_t size)
{
    H264Context * const h = avctx->priv_data;
    const PPS *pps = h->ps.pps;
    const SPS *sps = h->ps.sps;
    H264Picture *pic = h->cur_pic_ptr;
    struct vdpau_picture_context *pic_ctx = pic->hwaccel_picture_private;
    VdpPictureInfoH264 *info = &pic_ctx->info.h264;
#ifdef VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE
    VdpPictureInfoH264Predictive *info2 = &pic_ctx->info.h264_predictive;
#endif

    /* init VdpPictureInfoH264 */
    info->slice_count                            = 0;
    info->field_order_cnt[0]                     = h264_foc(pic->field_poc[0]);
    info->field_order_cnt[1]                     = h264_foc(pic->field_poc[1]);
    info->is_reference                           = h->nal_ref_idc != 0;
    info->frame_num                              = h->poc.frame_num;
    info->field_pic_flag                         = h->picture_structure != PICT_FRAME;
    info->bottom_field_flag                      = h->picture_structure == PICT_BOTTOM_FIELD;
    info->num_ref_frames                         = sps->ref_frame_count;
    info->mb_adaptive_frame_field_flag           = sps->mb_aff && !info->field_pic_flag;
    info->constrained_intra_pred_flag            = pps->constrained_intra_pred;
    info->weighted_pred_flag                     = pps->weighted_pred;
    info->weighted_bipred_idc                    = pps->weighted_bipred_idc;
    info->frame_mbs_only_flag                    = sps->frame_mbs_only_flag;
    info->transform_8x8_mode_flag                = pps->transform_8x8_mode;
    info->chroma_qp_index_offset                 = pps->chroma_qp_index_offset[0];
    info->second_chroma_qp_index_offset          = pps->chroma_qp_index_offset[1];
    info->pic_init_qp_minus26                    = pps->init_qp - 26;
    info->num_ref_idx_l0_active_minus1           = pps->ref_count[0] - 1;
    info->num_ref_idx_l1_active_minus1           = pps->ref_count[1] - 1;
    info->log2_max_frame_num_minus4              = sps->log2_max_frame_num - 4;
    info->pic_order_cnt_type                     = sps->poc_type;
    info->log2_max_pic_order_cnt_lsb_minus4      = sps->poc_type ? 0 : sps->log2_max_poc_lsb - 4;
    info->delta_pic_order_always_zero_flag       = sps->delta_pic_order_always_zero_flag;
    info->direct_8x8_inference_flag              = sps->direct_8x8_inference_flag;
#ifdef VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE
    info2->qpprime_y_zero_transform_bypass_flag  = sps->transform_bypass;
    info2->separate_colour_plane_flag            = sps->residual_color_transform_flag;
#endif
    info->entropy_coding_mode_flag               = pps->cabac;
    info->pic_order_present_flag                 = pps->pic_order_present;
    info->deblocking_filter_control_present_flag = pps->deblocking_filter_parameters_present;
    info->redundant_pic_cnt_present_flag         = pps->redundant_pic_cnt_present;

    memcpy(info->scaling_lists_4x4, pps->scaling_matrix4,
           sizeof(info->scaling_lists_4x4));
    memcpy(info->scaling_lists_8x8[0], pps->scaling_matrix8[0],
           sizeof(info->scaling_lists_8x8[0]));
    memcpy(info->scaling_lists_8x8[1], pps->scaling_matrix8[3],
           sizeof(info->scaling_lists_8x8[1]));

    vdpau_h264_set_reference_frames(avctx);

    return ff_vdpau_common_start_frame(pic_ctx, buffer, size);
}