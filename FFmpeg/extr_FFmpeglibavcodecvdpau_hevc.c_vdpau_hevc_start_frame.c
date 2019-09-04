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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_32__ {size_t num_short_term_ref_pic_sets; size_t num_tile_columns_minus1; size_t num_tile_rows_minus1; int pps_beta_offset_div2; int pps_tc_offset_div2; size_t CurrRpsIdx; uintptr_t* RefPics; int NumPocStCurrBefore; int NumPocStCurrAfter; int NumPocLtCurr; size_t* RefPicSetStCurrBefore; size_t* RefPicSetStCurrAfter; size_t* RefPicSetLtCurr; scalar_t__* IsLongTerm; scalar_t__* PicOrderCntVal; int /*<<< orphan*/  CurrPicOrderCntVal; int /*<<< orphan*/  NumLongTermPictureSliceHeaderBits; int /*<<< orphan*/  NumShortTermPictureSliceHeaderBits; int /*<<< orphan*/  NumDeltaPocsOfRefRpsIdx; int /*<<< orphan*/  NumPocTotalCurr; int /*<<< orphan*/  RAPPicFlag; int /*<<< orphan*/  IDRPicFlag; int /*<<< orphan*/  slice_segment_header_extension_present_flag; scalar_t__ log2_parallel_merge_level_minus2; int /*<<< orphan*/  lists_modification_present_flag; int /*<<< orphan*/  pps_deblocking_filter_disabled_flag; int /*<<< orphan*/  deblocking_filter_override_enabled_flag; int /*<<< orphan*/  deblocking_filter_control_present_flag; int /*<<< orphan*/  pps_loop_filter_across_slices_enabled_flag; int /*<<< orphan*/  loop_filter_across_tiles_enabled_flag; scalar_t__* row_height_minus1; scalar_t__* column_width_minus1; int /*<<< orphan*/  uniform_spacing_flag; scalar_t__ tiles_enabled_flag; int /*<<< orphan*/  entropy_coding_sync_enabled_flag; int /*<<< orphan*/  transquant_bypass_enabled_flag; int /*<<< orphan*/  weighted_bipred_flag; int /*<<< orphan*/  weighted_pred_flag; int /*<<< orphan*/  pps_slice_chroma_qp_offsets_present_flag; int /*<<< orphan*/  pps_cr_qp_offset; int /*<<< orphan*/  pps_cb_qp_offset; int /*<<< orphan*/  diff_cu_qp_delta_depth; int /*<<< orphan*/  cu_qp_delta_enabled_flag; int /*<<< orphan*/  transform_skip_enabled_flag; int /*<<< orphan*/  constrained_intra_pred_flag; int /*<<< orphan*/  init_qp_minus26; scalar_t__ num_ref_idx_l1_default_active_minus1; scalar_t__ num_ref_idx_l0_default_active_minus1; int /*<<< orphan*/  cabac_init_present_flag; int /*<<< orphan*/  sign_data_hiding_enabled_flag; int /*<<< orphan*/  num_extra_slice_header_bits; int /*<<< orphan*/  output_flag_present_flag; int /*<<< orphan*/  dependent_slice_segments_enabled_flag; int /*<<< orphan*/  strong_intra_smoothing_enabled_flag; int /*<<< orphan*/  sps_temporal_mvp_enabled_flag; int /*<<< orphan*/  num_long_term_ref_pics_sps; int /*<<< orphan*/  long_term_ref_pics_present_flag; int /*<<< orphan*/  pcm_loop_filter_disabled_flag; scalar_t__ log2_diff_max_min_pcm_luma_coding_block_size; scalar_t__ log2_min_pcm_luma_coding_block_size_minus3; scalar_t__ pcm_sample_bit_depth_chroma_minus1; scalar_t__ pcm_sample_bit_depth_luma_minus1; scalar_t__ pcm_enabled_flag; int /*<<< orphan*/  sample_adaptive_offset_enabled_flag; int /*<<< orphan*/  amp_enabled_flag; int /*<<< orphan*/ * ScalingListDCCoeff32x32; int /*<<< orphan*/ * ScalingListDCCoeff16x16; int /*<<< orphan*/ ** ScalingList32x32; int /*<<< orphan*/ ** ScalingList16x16; int /*<<< orphan*/ ** ScalingList8x8; int /*<<< orphan*/ ** ScalingList4x4; int /*<<< orphan*/  scaling_list_enabled_flag; int /*<<< orphan*/  max_transform_hierarchy_depth_intra; int /*<<< orphan*/  max_transform_hierarchy_depth_inter; scalar_t__ log2_diff_max_min_transform_block_size; scalar_t__ log2_min_transform_block_size_minus2; int /*<<< orphan*/  log2_diff_max_min_luma_coding_block_size; scalar_t__ log2_min_luma_coding_block_size_minus3; scalar_t__ sps_max_dec_pic_buffering_minus1; scalar_t__ log2_max_pic_order_cnt_lsb_minus4; scalar_t__ bit_depth_chroma_minus8; scalar_t__ bit_depth_luma_minus8; int /*<<< orphan*/  pic_height_in_luma_samples; int /*<<< orphan*/  pic_width_in_luma_samples; int /*<<< orphan*/  separate_colour_plane_flag; int /*<<< orphan*/  chroma_format_idc; } ;
struct TYPE_26__ {TYPE_7__ hevc; } ;
struct vdpau_picture_context {TYPE_1__ info; } ;
typedef  size_t ssize_t ;
typedef  TYPE_7__ VdpPictureInfoHEVC ;
struct TYPE_34__ {int /*<<< orphan*/ ** sl_dc; int /*<<< orphan*/ *** sl; } ;
struct TYPE_33__ {int short_term_ref_pic_set_sps_flag; int /*<<< orphan*/  long_term_ref_pic_set_size; int /*<<< orphan*/  short_term_ref_pic_set_size; TYPE_5__* short_term_rps; } ;
struct TYPE_31__ {int nb_refs; TYPE_12__ const** ref; } ;
struct TYPE_30__ {int /*<<< orphan*/  rps_idx_num_delta_pocs; } ;
struct TYPE_29__ {int /*<<< orphan*/  loop_filter_disable_flag; scalar_t__ log2_min_pcm_cb_size; scalar_t__ log2_max_pcm_cb_size; scalar_t__ bit_depth_chroma; scalar_t__ bit_depth; } ;
struct TYPE_28__ {scalar_t__ max_dec_pic_buffering; } ;
struct TYPE_27__ {TYPE_11__* pps; TYPE_10__* sps; } ;
struct TYPE_25__ {TYPE_13__* priv_data; } ;
struct TYPE_24__ {TYPE_6__* rps; TYPE_12__ const* ref; TYPE_12__ const* DPB; int /*<<< orphan*/  poc; TYPE_8__ sh; TYPE_2__ ps; } ;
struct TYPE_23__ {int flags; int /*<<< orphan*/  frame; scalar_t__ poc; struct vdpau_picture_context* hwaccel_picture_private; } ;
struct TYPE_22__ {size_t num_tile_columns; size_t num_tile_rows; int beta_offset; int tc_offset; int /*<<< orphan*/  slice_header_extension_present_flag; scalar_t__ log2_parallel_merge_level; int /*<<< orphan*/  lists_modification_present_flag; int /*<<< orphan*/  disable_dbf; int /*<<< orphan*/  deblocking_filter_override_enabled_flag; int /*<<< orphan*/  deblocking_filter_control_present_flag; int /*<<< orphan*/  seq_loop_filter_across_slices_enabled_flag; int /*<<< orphan*/  loop_filter_across_tiles_enabled_flag; scalar_t__* row_height; scalar_t__* column_width; int /*<<< orphan*/  uniform_spacing_flag; int /*<<< orphan*/  entropy_coding_sync_enabled_flag; scalar_t__ tiles_enabled_flag; int /*<<< orphan*/  transquant_bypass_enable_flag; int /*<<< orphan*/  weighted_bipred_flag; int /*<<< orphan*/  weighted_pred_flag; int /*<<< orphan*/  pic_slice_level_chroma_qp_offsets_present_flag; int /*<<< orphan*/  cr_qp_offset; int /*<<< orphan*/  cb_qp_offset; int /*<<< orphan*/  diff_cu_qp_delta_depth; int /*<<< orphan*/  cu_qp_delta_enabled_flag; int /*<<< orphan*/  transform_skip_enabled_flag; int /*<<< orphan*/  constrained_intra_pred_flag; int /*<<< orphan*/  pic_init_qp_minus26; scalar_t__ num_ref_idx_l1_default_active; scalar_t__ num_ref_idx_l0_default_active; int /*<<< orphan*/  cabac_init_present_flag; int /*<<< orphan*/  sign_data_hiding_flag; int /*<<< orphan*/  num_extra_slice_header_bits; int /*<<< orphan*/  output_flag_present_flag; int /*<<< orphan*/  dependent_slice_segments_enabled_flag; TYPE_9__ scaling_list; scalar_t__ scaling_list_data_present_flag; } ;
struct TYPE_21__ {int max_sub_layers; size_t nb_st_rps; TYPE_5__* st_rps; int /*<<< orphan*/  sps_strong_intra_smoothing_enable_flag; int /*<<< orphan*/  sps_temporal_mvp_enabled_flag; int /*<<< orphan*/  num_long_term_ref_pics_sps; int /*<<< orphan*/  long_term_ref_pics_present_flag; TYPE_4__ pcm; scalar_t__ pcm_enabled_flag; int /*<<< orphan*/  sao_enabled; int /*<<< orphan*/  amp_enabled_flag; int /*<<< orphan*/  scaling_list_enable_flag; int /*<<< orphan*/  max_transform_hierarchy_depth_intra; int /*<<< orphan*/  max_transform_hierarchy_depth_inter; scalar_t__ log2_min_tb_size; scalar_t__ log2_max_trafo_size; int /*<<< orphan*/  log2_diff_max_min_coding_block_size; scalar_t__ log2_min_cb_size; TYPE_3__* temporal_layer; scalar_t__ log2_max_poc_lsb; scalar_t__ bit_depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  separate_colour_plane_flag; int /*<<< orphan*/  chroma_format_idc; TYPE_9__ scaling_list; } ;
typedef  TYPE_8__ SliceHeader ;
typedef  TYPE_9__ ScalingList ;
typedef  TYPE_10__ HEVCSPS ;
typedef  TYPE_11__ HEVCPPS ;
typedef  TYPE_12__ const HEVCFrame ;
typedef  TYPE_13__ HEVCContext ;
typedef  TYPE_14__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 size_t FF_ARRAY_ELEMS (TYPE_12__ const*) ; 
 int HEVC_FRAME_FLAG_LONG_REF ; 
 int HEVC_FRAME_FLAG_SHORT_REF ; 
 int /*<<< orphan*/  IS_IDR (TYPE_13__*) ; 
 int /*<<< orphan*/  IS_IRAP (TYPE_13__*) ; 
 size_t LT_CURR ; 
 size_t ST_CURR_AFT ; 
 size_t ST_CURR_BEF ; 
 uintptr_t VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  av_log (TYPE_14__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t* ff_hevc_diag_scan4x4_x ; 
 int* ff_hevc_diag_scan4x4_y ; 
 size_t* ff_hevc_diag_scan8x8_x ; 
 int* ff_hevc_diag_scan8x8_y ; 
 int /*<<< orphan*/  ff_hevc_frame_nb_refs (TYPE_13__*) ; 
 int ff_vdpau_common_start_frame (struct vdpau_picture_context*,size_t const*,int /*<<< orphan*/ ) ; 
 void* ff_vdpau_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdpau_hevc_start_frame(AVCodecContext *avctx,
                                  const uint8_t *buffer, uint32_t size)
{
    HEVCContext *h = avctx->priv_data;
    HEVCFrame *pic = h->ref;
    struct vdpau_picture_context *pic_ctx = pic->hwaccel_picture_private;

    VdpPictureInfoHEVC *info = &pic_ctx->info.hevc;

    const HEVCSPS *sps = h->ps.sps;
    const HEVCPPS *pps = h->ps.pps;
    const SliceHeader *sh = &h->sh;
    const ScalingList *sl = pps->scaling_list_data_present_flag ?
                            &pps->scaling_list : &sps->scaling_list;

    /* init VdpPictureInfoHEVC */

    /* SPS */
    info->chroma_format_idc = sps->chroma_format_idc;
    info->separate_colour_plane_flag = sps->separate_colour_plane_flag;
    info->pic_width_in_luma_samples = sps->width;
    info->pic_height_in_luma_samples = sps->height;
    info->bit_depth_luma_minus8 = sps->bit_depth - 8;
    info->bit_depth_chroma_minus8 = sps->bit_depth - 8;
    info->log2_max_pic_order_cnt_lsb_minus4 = sps->log2_max_poc_lsb - 4;
    /* Provide the value corresponding to the nuh_temporal_id of the frame
       to be decoded. */
    info->sps_max_dec_pic_buffering_minus1 = sps->temporal_layer[sps->max_sub_layers - 1].max_dec_pic_buffering - 1;
    info->log2_min_luma_coding_block_size_minus3 = sps->log2_min_cb_size - 3;
    info->log2_diff_max_min_luma_coding_block_size = sps->log2_diff_max_min_coding_block_size;
    info->log2_min_transform_block_size_minus2 = sps->log2_min_tb_size - 2;
    info->log2_diff_max_min_transform_block_size = sps->log2_max_trafo_size - sps->log2_min_tb_size;
    info->max_transform_hierarchy_depth_inter = sps->max_transform_hierarchy_depth_inter;
    info->max_transform_hierarchy_depth_intra = sps->max_transform_hierarchy_depth_intra;
    info->scaling_list_enabled_flag = sps->scaling_list_enable_flag;
    /* Scaling lists, in diagonal order, to be used for this frame. */
    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 16; j++) {
            /* Scaling List for 4x4 quantization matrix,
               indexed as ScalingList4x4[matrixId][i]. */
            uint8_t pos = 4 * ff_hevc_diag_scan4x4_y[j] + ff_hevc_diag_scan4x4_x[j];
            info->ScalingList4x4[i][j] = sl->sl[0][i][pos];
        }
        for (size_t j = 0; j < 64; j++) {
            uint8_t pos = 8 * ff_hevc_diag_scan8x8_y[j] + ff_hevc_diag_scan8x8_x[j];
            /* Scaling List for 8x8 quantization matrix,
               indexed as ScalingList8x8[matrixId][i]. */
            info->ScalingList8x8[i][j] = sl->sl[1][i][pos];
            /* Scaling List for 16x16 quantization matrix,
               indexed as ScalingList16x16[matrixId][i]. */
            info->ScalingList16x16[i][j] = sl->sl[2][i][pos];
            if (i < 2) {
                /* Scaling List for 32x32 quantization matrix,
                   indexed as ScalingList32x32[matrixId][i]. */
                info->ScalingList32x32[i][j] = sl->sl[3][i * 3][pos];
            }
        }
        /* Scaling List DC Coefficients for 16x16,
           indexed as ScalingListDCCoeff16x16[matrixId]. */
        info->ScalingListDCCoeff16x16[i] = sl->sl_dc[0][i];
        if (i < 2) {
            /* Scaling List DC Coefficients for 32x32,
               indexed as ScalingListDCCoeff32x32[matrixId]. */
            info->ScalingListDCCoeff32x32[i] = sl->sl_dc[1][i * 3];
        }
    }
    info->amp_enabled_flag = sps->amp_enabled_flag;
    info->sample_adaptive_offset_enabled_flag = sps->sao_enabled;
    info->pcm_enabled_flag = sps->pcm_enabled_flag;
    if (info->pcm_enabled_flag) {
        /* Only needs to be set if pcm_enabled_flag is set. Ignored otherwise. */
        info->pcm_sample_bit_depth_luma_minus1 = sps->pcm.bit_depth - 1;
        /* Only needs to be set if pcm_enabled_flag is set. Ignored otherwise. */
        info->pcm_sample_bit_depth_chroma_minus1 = sps->pcm.bit_depth_chroma - 1;
        /* Only needs to be set if pcm_enabled_flag is set. Ignored otherwise. */
        info->log2_min_pcm_luma_coding_block_size_minus3 = sps->pcm.log2_min_pcm_cb_size - 3;
        /* Only needs to be set if pcm_enabled_flag is set. Ignored otherwise. */
        info->log2_diff_max_min_pcm_luma_coding_block_size = sps->pcm.log2_max_pcm_cb_size - sps->pcm.log2_min_pcm_cb_size;
        /* Only needs to be set if pcm_enabled_flag is set. Ignored otherwise. */
        info->pcm_loop_filter_disabled_flag = sps->pcm.loop_filter_disable_flag;
    }
    /* Per spec, when zero, assume short_term_ref_pic_set_sps_flag
       is also zero. */
    info->num_short_term_ref_pic_sets = sps->nb_st_rps;
    info->long_term_ref_pics_present_flag = sps->long_term_ref_pics_present_flag;
    /* Only needed if long_term_ref_pics_present_flag is set. Ignored
       otherwise. */
    info->num_long_term_ref_pics_sps = sps->num_long_term_ref_pics_sps;
    info->sps_temporal_mvp_enabled_flag = sps->sps_temporal_mvp_enabled_flag;
    info->strong_intra_smoothing_enabled_flag = sps->sps_strong_intra_smoothing_enable_flag;

    /* Copy the HEVC Picture Parameter Set bitstream fields. */
    info->dependent_slice_segments_enabled_flag = pps->dependent_slice_segments_enabled_flag;
    info->output_flag_present_flag = pps->output_flag_present_flag;
    info->num_extra_slice_header_bits = pps->num_extra_slice_header_bits;
    info->sign_data_hiding_enabled_flag = pps->sign_data_hiding_flag;
    info->cabac_init_present_flag = pps->cabac_init_present_flag;
    info->num_ref_idx_l0_default_active_minus1 = pps->num_ref_idx_l0_default_active - 1;
    info->num_ref_idx_l1_default_active_minus1 = pps->num_ref_idx_l1_default_active - 1;
    info->init_qp_minus26 = pps->pic_init_qp_minus26;
    info->constrained_intra_pred_flag = pps->constrained_intra_pred_flag;
    info->transform_skip_enabled_flag = pps->transform_skip_enabled_flag;
    info->cu_qp_delta_enabled_flag = pps->cu_qp_delta_enabled_flag;
    /* Only needed if cu_qp_delta_enabled_flag is set. Ignored otherwise. */
    info->diff_cu_qp_delta_depth = pps->diff_cu_qp_delta_depth;
    info->pps_cb_qp_offset = pps->cb_qp_offset;
    info->pps_cr_qp_offset = pps->cr_qp_offset;
    info->pps_slice_chroma_qp_offsets_present_flag = pps->pic_slice_level_chroma_qp_offsets_present_flag;
    info->weighted_pred_flag = pps->weighted_pred_flag;
    info->weighted_bipred_flag = pps->weighted_bipred_flag;
    info->transquant_bypass_enabled_flag = pps->transquant_bypass_enable_flag;
    info->tiles_enabled_flag = pps->tiles_enabled_flag;
    info->entropy_coding_sync_enabled_flag = pps->entropy_coding_sync_enabled_flag;
    if (info->tiles_enabled_flag) {
        /* Only valid if tiles_enabled_flag is set. Ignored otherwise. */
        info->num_tile_columns_minus1 = pps->num_tile_columns - 1;
        /* Only valid if tiles_enabled_flag is set. Ignored otherwise. */
        info->num_tile_rows_minus1 = pps->num_tile_rows - 1;
        /* Only valid if tiles_enabled_flag is set. Ignored otherwise. */
        info->uniform_spacing_flag = pps->uniform_spacing_flag;
        /* Only need to set 0..num_tile_columns_minus1. The struct
           definition reserves up to the maximum of 20. Invalid values are
           ignored. */
        for (ssize_t i = 0; i < pps->num_tile_columns; i++) {
            info->column_width_minus1[i] = pps->column_width[i] - 1;
        }
        /* Only need to set 0..num_tile_rows_minus1. The struct
           definition reserves up to the maximum of 22. Invalid values are
           ignored.*/
        for (ssize_t i = 0; i < pps->num_tile_rows; i++) {
            info->row_height_minus1[i] = pps->row_height[i] - 1;
        }
        /* Only needed if tiles_enabled_flag is set. Invalid values are
           ignored. */
        info->loop_filter_across_tiles_enabled_flag = pps->loop_filter_across_tiles_enabled_flag;
    }
    info->pps_loop_filter_across_slices_enabled_flag = pps->seq_loop_filter_across_slices_enabled_flag;
    info->deblocking_filter_control_present_flag = pps->deblocking_filter_control_present_flag;
    /* Only valid if deblocking_filter_control_present_flag is set. Ignored
       otherwise. */
    info->deblocking_filter_override_enabled_flag = pps->deblocking_filter_override_enabled_flag;
    /* Only valid if deblocking_filter_control_present_flag is set. Ignored
       otherwise. */
    info->pps_deblocking_filter_disabled_flag = pps->disable_dbf;
    /* Only valid if deblocking_filter_control_present_flag is set and
       pps_deblocking_filter_disabled_flag is not set. Ignored otherwise.*/
    info->pps_beta_offset_div2 = pps->beta_offset / 2;
    /* Only valid if deblocking_filter_control_present_flag is set and
       pps_deblocking_filter_disabled_flag is not set. Ignored otherwise. */
    info->pps_tc_offset_div2 = pps->tc_offset / 2;
    info->lists_modification_present_flag = pps->lists_modification_present_flag;
    info->log2_parallel_merge_level_minus2 = pps->log2_parallel_merge_level - 2;
    info->slice_segment_header_extension_present_flag = pps->slice_header_extension_present_flag;

    /* Set to 1 if nal_unit_type is equal to IDR_W_RADL or IDR_N_LP.
       Set to zero otherwise. */
    info->IDRPicFlag = IS_IDR(h);
    /* Set to 1 if nal_unit_type in the range of BLA_W_LP to
       RSV_IRAP_VCL23, inclusive. Set to zero otherwise.*/
    info->RAPPicFlag = IS_IRAP(h);
    /* See section 7.4.7.1 of the specification. */
    info->CurrRpsIdx = sps->nb_st_rps;
    if (sh->short_term_ref_pic_set_sps_flag == 1) {
        for (size_t i = 0; i < sps->nb_st_rps; i++) {
            if (sh->short_term_rps == &sps->st_rps[i]) {
                info->CurrRpsIdx = i;
                break;
            }
        }
    }
    /* See section 7.4.7.2 of the specification. */
    info->NumPocTotalCurr = ff_hevc_frame_nb_refs(h);
    if (sh->short_term_ref_pic_set_sps_flag == 0 && sh->short_term_rps) {
        /* Corresponds to specification field, NumDeltaPocs[RefRpsIdx].
           Only applicable when short_term_ref_pic_set_sps_flag == 0.
           Implementations will ignore this value in other cases. See 7.4.8. */
        info->NumDeltaPocsOfRefRpsIdx = sh->short_term_rps->rps_idx_num_delta_pocs;
    }
    /* Section 7.6.3.1 of the H.265/HEVC Specification defines the syntax of
       the slice_segment_header. This header contains information that
       some VDPAU implementations may choose to skip. The VDPAU API
       requires client applications to track the number of bits used in the
       slice header for structures associated with short term and long term
       reference pictures. First, VDPAU requires the number of bits used by
       the short_term_ref_pic_set array in the slice_segment_header. */
    info->NumShortTermPictureSliceHeaderBits = sh->short_term_ref_pic_set_size;
    /* Second, VDPAU requires the number of bits used for long term reference
       pictures in the slice_segment_header. This is equal to the number
       of bits used for the contents of the block beginning with
       "if(long_term_ref_pics_present_flag)". */
    info->NumLongTermPictureSliceHeaderBits = sh->long_term_ref_pic_set_size;

    /* The value of PicOrderCntVal of the picture in the access unit
       containing the SEI message. The picture being decoded. */
    info->CurrPicOrderCntVal = h->poc;

    /* Slice Decoding Process - Reference Picture Sets */
    for (size_t i = 0; i < 16; i++) {
        info->RefPics[i] = VDP_INVALID_HANDLE;
        info->PicOrderCntVal[i] = 0;
        info->IsLongTerm[i] = 0;
    }
    for (size_t i = 0, j = 0; i < FF_ARRAY_ELEMS(h->DPB); i++) {
        const HEVCFrame *frame = &h->DPB[i];
        if (frame != h->ref && (frame->flags & (HEVC_FRAME_FLAG_LONG_REF |
                                                HEVC_FRAME_FLAG_SHORT_REF))) {
            if (j > 15) {
                av_log(avctx, AV_LOG_WARNING,
                     "VDPAU only supports up to 16 references in the DPB. "
                     "This frame may not be decoded correctly.\n");
                break;
            }
            /* Array of video reference surfaces.
               Set any unused positions to VDP_INVALID_HANDLE. */
            info->RefPics[j] = ff_vdpau_get_surface_id(frame->frame);
            /* Array of picture order counts. These correspond to positions
               in the RefPics array. */
            info->PicOrderCntVal[j] = frame->poc;
            /* Array used to specify whether a particular RefPic is
               a long term reference. A value of "1" indicates a long-term
               reference. */
            // XXX: Setting this caused glitches in the nvidia implementation
            // Always setting it to zero, produces correct results
            //info->IsLongTerm[j] = frame->flags & HEVC_FRAME_FLAG_LONG_REF;
            info->IsLongTerm[j] = 0;
            j++;
        }
    }
    /* Copy of specification field, see Section 8.3.2 of the
       H.265/HEVC Specification. */
    info->NumPocStCurrBefore = h->rps[ST_CURR_BEF].nb_refs;
    if (info->NumPocStCurrBefore > 8) {
        av_log(avctx, AV_LOG_WARNING,
             "VDPAU only supports up to 8 references in StCurrBefore. "
             "This frame may not be decoded correctly.\n");
        info->NumPocStCurrBefore = 8;
    }
    /* Copy of specification field, see Section 8.3.2 of the
       H.265/HEVC Specification. */
    info->NumPocStCurrAfter = h->rps[ST_CURR_AFT].nb_refs;
    if (info->NumPocStCurrAfter > 8) {
        av_log(avctx, AV_LOG_WARNING,
             "VDPAU only supports up to 8 references in StCurrAfter. "
             "This frame may not be decoded correctly.\n");
        info->NumPocStCurrAfter = 8;
    }
    /* Copy of specification field, see Section 8.3.2 of the
       H.265/HEVC Specification. */
    info->NumPocLtCurr = h->rps[LT_CURR].nb_refs;
    if (info->NumPocLtCurr > 8) {
        av_log(avctx, AV_LOG_WARNING,
             "VDPAU only supports up to 8 references in LtCurr. "
             "This frame may not be decoded correctly.\n");
        info->NumPocLtCurr = 8;
    }
    /* Reference Picture Set list, one of the short-term RPS. These
       correspond to positions in the RefPics array. */
    for (ssize_t i = 0, j = 0; i < h->rps[ST_CURR_BEF].nb_refs; i++) {
        HEVCFrame *frame = h->rps[ST_CURR_BEF].ref[i];
        if (frame) {
            uint8_t found = 0;
            uintptr_t id = ff_vdpau_get_surface_id(frame->frame);
            for (size_t k = 0; k < 16; k++) {
                if (id == info->RefPics[k]) {
                    info->RefPicSetStCurrBefore[j] = k;
                    j++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                av_log(avctx, AV_LOG_WARNING, "missing surface: %p\n",
                       (void *)id);
            }
        } else {
            av_log(avctx, AV_LOG_WARNING, "missing STR Before frame: %zd\n", i);
        }
    }
    /* Reference Picture Set list, one of the short-term RPS. These
       correspond to positions in the RefPics array. */
    for (ssize_t i = 0, j = 0; i < h->rps[ST_CURR_AFT].nb_refs; i++) {
        HEVCFrame *frame = h->rps[ST_CURR_AFT].ref[i];
        if (frame) {
            uint8_t found = 0;
            uintptr_t id = ff_vdpau_get_surface_id(frame->frame);
            for (size_t k = 0; k < 16; k++) {
                if (id == info->RefPics[k]) {
                    info->RefPicSetStCurrAfter[j] = k;
                    j++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                av_log(avctx, AV_LOG_WARNING, "missing surface: %p\n",
                       (void *)id);
            }
        } else {
            av_log(avctx, AV_LOG_WARNING, "missing STR After frame: %zd\n", i);
        }
    }
    /* Reference Picture Set list, one of the long-term RPS. These
       correspond to positions in the RefPics array. */
    for (ssize_t i = 0, j = 0; i < h->rps[LT_CURR].nb_refs; i++) {
        HEVCFrame *frame = h->rps[LT_CURR].ref[i];
        if (frame) {
            uint8_t found = 0;
            uintptr_t id = ff_vdpau_get_surface_id(frame->frame);
            for (size_t k = 0; k < 16; k++) {
                if (id == info->RefPics[k]) {
                    info->RefPicSetLtCurr[j] = k;
                    j++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                av_log(avctx, AV_LOG_WARNING, "missing surface: %p\n",
                       (void *)id);
            }
        } else {
            av_log(avctx, AV_LOG_WARNING, "missing LTR frame: %zd\n", i);
        }
    }

    return ff_vdpau_common_start_frame(pic_ctx, buffer, size);
}