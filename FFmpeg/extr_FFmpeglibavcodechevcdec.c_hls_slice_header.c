#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_37__ {size_t sps_id; int num_extra_slice_header_bits; int num_ref_idx_l0_default_active; int num_ref_idx_l1_default_active; int disable_dbf; int beta_offset; int tc_offset; int seq_loop_filter_across_slices_enabled_flag; int num_tile_rows; int num_tile_columns; int pic_init_qp_minus26; int /*<<< orphan*/  cu_qp_delta_enabled_flag; scalar_t__ slice_header_extension_present_flag; scalar_t__ entropy_coding_sync_enabled_flag; scalar_t__ tiles_enabled_flag; scalar_t__ deblocking_filter_override_enabled_flag; scalar_t__ deblocking_filter_control_present_flag; scalar_t__ chroma_qp_offset_list_enabled_flag; scalar_t__ pic_slice_level_chroma_qp_offsets_present_flag; scalar_t__ weighted_bipred_flag; scalar_t__ weighted_pred_flag; scalar_t__ cabac_init_present_flag; scalar_t__ lists_modification_present_flag; scalar_t__ output_flag_present_flag; scalar_t__ dependent_slice_segments_enabled_flag; } ;
struct TYPE_36__ {scalar_t__ width; scalar_t__ height; int max_sub_layers; int ctb_width; int ctb_height; int log2_max_poc_lsb; int nb_st_rps; int qp_bd_offset; scalar_t__ chroma_format_idc; scalar_t__ sao_enabled; scalar_t__ sps_temporal_mvp_enabled_flag; int /*<<< orphan*/ * st_rps; scalar_t__ separate_colour_plane_flag; int /*<<< orphan*/  pix_fmt; TYPE_3__* temporal_layer; } ;
struct TYPE_35__ {int first_slice_in_pic_flag; int no_output_of_prior_pics_flag; int pps_id; int dependent_slice_segment_flag; int slice_segment_addr; unsigned int slice_addr; int slice_type; int pic_output_flag; int short_term_ref_pic_set_sps_flag; int short_term_ref_pic_set_size; int long_term_ref_pic_set_size; int slice_temporal_mvp_enabled_flag; int* slice_sample_adaptive_offset_flag; int* nb_refs; int* rpl_modification_flag; int mvd_l1_zero_flag; int cabac_init_flag; int collocated_ref_idx; size_t collocated_list; int max_num_merge_cand; int slice_qp_delta; int cu_chroma_qp_offset_enabled_flag; int disable_deblocking_filter_flag; int beta_offset; int tc_offset; int slice_loop_filter_across_slices_enabled_flag; unsigned int num_entry_point_offsets; unsigned int* entry_point_offset; unsigned int* offset; unsigned int* size; int slice_qp; unsigned int slice_ctb_addr_rs; void* slice_cr_qp_offset; void* slice_cb_qp_offset; void*** list_entry_lx; int /*<<< orphan*/ * short_term_rps; int /*<<< orphan*/  long_term_rps; int /*<<< orphan*/  slice_rps; void* pic_order_cnt_lsb; void* colour_plane_id; } ;
struct TYPE_33__ {scalar_t__ cu_qp_offset_cr; scalar_t__ cu_qp_offset_cb; } ;
struct TYPE_34__ {int first_qp_group; int qp_y; TYPE_5__ tu; int /*<<< orphan*/  gb; } ;
struct TYPE_32__ {TYPE_9__* pps; TYPE_8__* sps; TYPE_2__** sps_list; TYPE_1__** pps_list; } ;
struct TYPE_31__ {scalar_t__ max_dec_pic_buffering; } ;
struct TYPE_30__ {scalar_t__ data; } ;
struct TYPE_29__ {scalar_t__ data; } ;
struct TYPE_28__ {int pix_fmt; int err_recognition; } ;
struct TYPE_27__ {int seq_decode; scalar_t__ nal_unit_type; int last_eos; int slice_initialized; int pocTid0; int poc; scalar_t__ temporal_id; int threads_number; TYPE_6__* HEVClc; TYPE_7__ sh; TYPE_4__ ps; TYPE_18__* avctx; scalar_t__ enable_parallel_tiles; scalar_t__ slice_idx; void* max_ra; scalar_t__ ref; } ;
typedef  TYPE_7__ SliceHeader ;
typedef  TYPE_8__ HEVCSPS ;
typedef  TYPE_9__ HEVCPPS ;
typedef  TYPE_10__ HEVCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HEVC_MAX_PPS_COUNT ; 
 int HEVC_MAX_REFS ; 
 scalar_t__ HEVC_NAL_CRA_NUT ; 
 scalar_t__ HEVC_NAL_RADL_N ; 
 scalar_t__ HEVC_NAL_RADL_R ; 
 scalar_t__ HEVC_NAL_RASL_N ; 
 scalar_t__ HEVC_NAL_RASL_R ; 
 scalar_t__ HEVC_NAL_STSA_N ; 
 scalar_t__ HEVC_NAL_TRAIL_N ; 
 scalar_t__ HEVC_NAL_TSA_N ; 
 int HEVC_SLICE_B ; 
 int HEVC_SLICE_I ; 
 int HEVC_SLICE_P ; 
 void* INT_MAX ; 
 scalar_t__ IS_BLA (TYPE_10__*) ; 
 scalar_t__ IS_IDR (TYPE_10__*) ; 
 scalar_t__ IS_IRAP (TYPE_10__*) ; 
 size_t L0 ; 
 size_t L1 ; 
 int av_ceil_log2 (int) ; 
 int /*<<< orphan*/  av_freep (unsigned int**) ; 
 int /*<<< orphan*/  av_log (TYPE_18__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_malloc_array (unsigned int,int) ; 
 int decode_lt_rps (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_hevc_clear_refs (TYPE_10__*) ; 
 int ff_hevc_compute_poc (TYPE_8__*,int,void*,scalar_t__) ; 
 int ff_hevc_decode_short_term_rps (int /*<<< orphan*/ *,TYPE_18__*,int /*<<< orphan*/ *,TYPE_8__*,int) ; 
 int ff_hevc_frame_nb_refs (TYPE_10__*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 
 int get_bitsz (int /*<<< orphan*/ *,int) ; 
 int get_format (TYPE_10__*,TYPE_8__ const*) ; 
 void* get_se_golomb (int /*<<< orphan*/ *) ; 
 int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int pred_weight_table (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int set_sps (TYPE_10__*,TYPE_8__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hls_slice_header(HEVCContext *s)
{
    GetBitContext *gb = &s->HEVClc->gb;
    SliceHeader *sh   = &s->sh;
    int i, ret;

    // Coded parameters
    sh->first_slice_in_pic_flag = get_bits1(gb);
    if (s->ref && sh->first_slice_in_pic_flag) {
        av_log(s->avctx, AV_LOG_ERROR, "Two slices reporting being the first in the same frame.\n");
        return 1; // This slice will be skiped later, do not corrupt state
    }

    if ((IS_IDR(s) || IS_BLA(s)) && sh->first_slice_in_pic_flag) {
        s->seq_decode = (s->seq_decode + 1) & 0xff;
        s->max_ra     = INT_MAX;
        if (IS_IDR(s))
            ff_hevc_clear_refs(s);
    }
    sh->no_output_of_prior_pics_flag = 0;
    if (IS_IRAP(s))
        sh->no_output_of_prior_pics_flag = get_bits1(gb);

    sh->pps_id = get_ue_golomb_long(gb);
    if (sh->pps_id >= HEVC_MAX_PPS_COUNT || !s->ps.pps_list[sh->pps_id]) {
        av_log(s->avctx, AV_LOG_ERROR, "PPS id out of range: %d\n", sh->pps_id);
        return AVERROR_INVALIDDATA;
    }
    if (!sh->first_slice_in_pic_flag &&
        s->ps.pps != (HEVCPPS*)s->ps.pps_list[sh->pps_id]->data) {
        av_log(s->avctx, AV_LOG_ERROR, "PPS changed between slices.\n");
        return AVERROR_INVALIDDATA;
    }
    s->ps.pps = (HEVCPPS*)s->ps.pps_list[sh->pps_id]->data;
    if (s->nal_unit_type == HEVC_NAL_CRA_NUT && s->last_eos == 1)
        sh->no_output_of_prior_pics_flag = 1;

    if (s->ps.sps != (HEVCSPS*)s->ps.sps_list[s->ps.pps->sps_id]->data) {
        const HEVCSPS *sps = (HEVCSPS*)s->ps.sps_list[s->ps.pps->sps_id]->data;
        const HEVCSPS *last_sps = s->ps.sps;
        enum AVPixelFormat pix_fmt;

        if (last_sps && IS_IRAP(s) && s->nal_unit_type != HEVC_NAL_CRA_NUT) {
            if (sps->width != last_sps->width || sps->height != last_sps->height ||
                sps->temporal_layer[sps->max_sub_layers - 1].max_dec_pic_buffering !=
                last_sps->temporal_layer[last_sps->max_sub_layers - 1].max_dec_pic_buffering)
                sh->no_output_of_prior_pics_flag = 0;
        }
        ff_hevc_clear_refs(s);

        ret = set_sps(s, sps, sps->pix_fmt);
        if (ret < 0)
            return ret;

        pix_fmt = get_format(s, sps);
        if (pix_fmt < 0)
            return pix_fmt;
        s->avctx->pix_fmt = pix_fmt;

        s->seq_decode = (s->seq_decode + 1) & 0xff;
        s->max_ra     = INT_MAX;
    }

    sh->dependent_slice_segment_flag = 0;
    if (!sh->first_slice_in_pic_flag) {
        int slice_address_length;

        if (s->ps.pps->dependent_slice_segments_enabled_flag)
            sh->dependent_slice_segment_flag = get_bits1(gb);

        slice_address_length = av_ceil_log2(s->ps.sps->ctb_width *
                                            s->ps.sps->ctb_height);
        sh->slice_segment_addr = get_bitsz(gb, slice_address_length);
        if (sh->slice_segment_addr >= s->ps.sps->ctb_width * s->ps.sps->ctb_height) {
            av_log(s->avctx, AV_LOG_ERROR,
                   "Invalid slice segment address: %u.\n",
                   sh->slice_segment_addr);
            return AVERROR_INVALIDDATA;
        }

        if (!sh->dependent_slice_segment_flag) {
            sh->slice_addr = sh->slice_segment_addr;
            s->slice_idx++;
        }
    } else {
        sh->slice_segment_addr = sh->slice_addr = 0;
        s->slice_idx           = 0;
        s->slice_initialized   = 0;
    }

    if (!sh->dependent_slice_segment_flag) {
        s->slice_initialized = 0;

        for (i = 0; i < s->ps.pps->num_extra_slice_header_bits; i++)
            skip_bits(gb, 1);  // slice_reserved_undetermined_flag[]

        sh->slice_type = get_ue_golomb_long(gb);
        if (!(sh->slice_type == HEVC_SLICE_I ||
              sh->slice_type == HEVC_SLICE_P ||
              sh->slice_type == HEVC_SLICE_B)) {
            av_log(s->avctx, AV_LOG_ERROR, "Unknown slice type: %d.\n",
                   sh->slice_type);
            return AVERROR_INVALIDDATA;
        }
        if (IS_IRAP(s) && sh->slice_type != HEVC_SLICE_I) {
            av_log(s->avctx, AV_LOG_ERROR, "Inter slices in an IRAP frame.\n");
            return AVERROR_INVALIDDATA;
        }

        // when flag is not present, picture is inferred to be output
        sh->pic_output_flag = 1;
        if (s->ps.pps->output_flag_present_flag)
            sh->pic_output_flag = get_bits1(gb);

        if (s->ps.sps->separate_colour_plane_flag)
            sh->colour_plane_id = get_bits(gb, 2);

        if (!IS_IDR(s)) {
            int poc, pos;

            sh->pic_order_cnt_lsb = get_bits(gb, s->ps.sps->log2_max_poc_lsb);
            poc = ff_hevc_compute_poc(s->ps.sps, s->pocTid0, sh->pic_order_cnt_lsb, s->nal_unit_type);
            if (!sh->first_slice_in_pic_flag && poc != s->poc) {
                av_log(s->avctx, AV_LOG_WARNING,
                       "Ignoring POC change between slices: %d -> %d\n", s->poc, poc);
                if (s->avctx->err_recognition & AV_EF_EXPLODE)
                    return AVERROR_INVALIDDATA;
                poc = s->poc;
            }
            s->poc = poc;

            sh->short_term_ref_pic_set_sps_flag = get_bits1(gb);
            pos = get_bits_left(gb);
            if (!sh->short_term_ref_pic_set_sps_flag) {
                ret = ff_hevc_decode_short_term_rps(gb, s->avctx, &sh->slice_rps, s->ps.sps, 1);
                if (ret < 0)
                    return ret;

                sh->short_term_rps = &sh->slice_rps;
            } else {
                int numbits, rps_idx;

                if (!s->ps.sps->nb_st_rps) {
                    av_log(s->avctx, AV_LOG_ERROR, "No ref lists in the SPS.\n");
                    return AVERROR_INVALIDDATA;
                }

                numbits = av_ceil_log2(s->ps.sps->nb_st_rps);
                rps_idx = numbits > 0 ? get_bits(gb, numbits) : 0;
                sh->short_term_rps = &s->ps.sps->st_rps[rps_idx];
            }
            sh->short_term_ref_pic_set_size = pos - get_bits_left(gb);

            pos = get_bits_left(gb);
            ret = decode_lt_rps(s, &sh->long_term_rps, gb);
            if (ret < 0) {
                av_log(s->avctx, AV_LOG_WARNING, "Invalid long term RPS.\n");
                if (s->avctx->err_recognition & AV_EF_EXPLODE)
                    return AVERROR_INVALIDDATA;
            }
            sh->long_term_ref_pic_set_size = pos - get_bits_left(gb);

            if (s->ps.sps->sps_temporal_mvp_enabled_flag)
                sh->slice_temporal_mvp_enabled_flag = get_bits1(gb);
            else
                sh->slice_temporal_mvp_enabled_flag = 0;
        } else {
            s->sh.short_term_rps = NULL;
            s->poc               = 0;
        }

        /* 8.3.1 */
        if (sh->first_slice_in_pic_flag && s->temporal_id == 0 &&
            s->nal_unit_type != HEVC_NAL_TRAIL_N &&
            s->nal_unit_type != HEVC_NAL_TSA_N   &&
            s->nal_unit_type != HEVC_NAL_STSA_N  &&
            s->nal_unit_type != HEVC_NAL_RADL_N  &&
            s->nal_unit_type != HEVC_NAL_RADL_R  &&
            s->nal_unit_type != HEVC_NAL_RASL_N  &&
            s->nal_unit_type != HEVC_NAL_RASL_R)
            s->pocTid0 = s->poc;

        if (s->ps.sps->sao_enabled) {
            sh->slice_sample_adaptive_offset_flag[0] = get_bits1(gb);
            if (s->ps.sps->chroma_format_idc) {
                sh->slice_sample_adaptive_offset_flag[1] =
                sh->slice_sample_adaptive_offset_flag[2] = get_bits1(gb);
            }
        } else {
            sh->slice_sample_adaptive_offset_flag[0] = 0;
            sh->slice_sample_adaptive_offset_flag[1] = 0;
            sh->slice_sample_adaptive_offset_flag[2] = 0;
        }

        sh->nb_refs[L0] = sh->nb_refs[L1] = 0;
        if (sh->slice_type == HEVC_SLICE_P || sh->slice_type == HEVC_SLICE_B) {
            int nb_refs;

            sh->nb_refs[L0] = s->ps.pps->num_ref_idx_l0_default_active;
            if (sh->slice_type == HEVC_SLICE_B)
                sh->nb_refs[L1] = s->ps.pps->num_ref_idx_l1_default_active;

            if (get_bits1(gb)) { // num_ref_idx_active_override_flag
                sh->nb_refs[L0] = get_ue_golomb_long(gb) + 1;
                if (sh->slice_type == HEVC_SLICE_B)
                    sh->nb_refs[L1] = get_ue_golomb_long(gb) + 1;
            }
            if (sh->nb_refs[L0] > HEVC_MAX_REFS || sh->nb_refs[L1] > HEVC_MAX_REFS) {
                av_log(s->avctx, AV_LOG_ERROR, "Too many refs: %d/%d.\n",
                       sh->nb_refs[L0], sh->nb_refs[L1]);
                return AVERROR_INVALIDDATA;
            }

            sh->rpl_modification_flag[0] = 0;
            sh->rpl_modification_flag[1] = 0;
            nb_refs = ff_hevc_frame_nb_refs(s);
            if (!nb_refs) {
                av_log(s->avctx, AV_LOG_ERROR, "Zero refs for a frame with P or B slices.\n");
                return AVERROR_INVALIDDATA;
            }

            if (s->ps.pps->lists_modification_present_flag && nb_refs > 1) {
                sh->rpl_modification_flag[0] = get_bits1(gb);
                if (sh->rpl_modification_flag[0]) {
                    for (i = 0; i < sh->nb_refs[L0]; i++)
                        sh->list_entry_lx[0][i] = get_bits(gb, av_ceil_log2(nb_refs));
                }

                if (sh->slice_type == HEVC_SLICE_B) {
                    sh->rpl_modification_flag[1] = get_bits1(gb);
                    if (sh->rpl_modification_flag[1] == 1)
                        for (i = 0; i < sh->nb_refs[L1]; i++)
                            sh->list_entry_lx[1][i] = get_bits(gb, av_ceil_log2(nb_refs));
                }
            }

            if (sh->slice_type == HEVC_SLICE_B)
                sh->mvd_l1_zero_flag = get_bits1(gb);

            if (s->ps.pps->cabac_init_present_flag)
                sh->cabac_init_flag = get_bits1(gb);
            else
                sh->cabac_init_flag = 0;

            sh->collocated_ref_idx = 0;
            if (sh->slice_temporal_mvp_enabled_flag) {
                sh->collocated_list = L0;
                if (sh->slice_type == HEVC_SLICE_B)
                    sh->collocated_list = !get_bits1(gb);

                if (sh->nb_refs[sh->collocated_list] > 1) {
                    sh->collocated_ref_idx = get_ue_golomb_long(gb);
                    if (sh->collocated_ref_idx >= sh->nb_refs[sh->collocated_list]) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "Invalid collocated_ref_idx: %d.\n",
                               sh->collocated_ref_idx);
                        return AVERROR_INVALIDDATA;
                    }
                }
            }

            if ((s->ps.pps->weighted_pred_flag   && sh->slice_type == HEVC_SLICE_P) ||
                (s->ps.pps->weighted_bipred_flag && sh->slice_type == HEVC_SLICE_B)) {
                int ret = pred_weight_table(s, gb);
                if (ret < 0)
                    return ret;
            }

            sh->max_num_merge_cand = 5 - get_ue_golomb_long(gb);
            if (sh->max_num_merge_cand < 1 || sh->max_num_merge_cand > 5) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "Invalid number of merging MVP candidates: %d.\n",
                       sh->max_num_merge_cand);
                return AVERROR_INVALIDDATA;
            }
        }

        sh->slice_qp_delta = get_se_golomb(gb);

        if (s->ps.pps->pic_slice_level_chroma_qp_offsets_present_flag) {
            sh->slice_cb_qp_offset = get_se_golomb(gb);
            sh->slice_cr_qp_offset = get_se_golomb(gb);
        } else {
            sh->slice_cb_qp_offset = 0;
            sh->slice_cr_qp_offset = 0;
        }

        if (s->ps.pps->chroma_qp_offset_list_enabled_flag)
            sh->cu_chroma_qp_offset_enabled_flag = get_bits1(gb);
        else
            sh->cu_chroma_qp_offset_enabled_flag = 0;

        if (s->ps.pps->deblocking_filter_control_present_flag) {
            int deblocking_filter_override_flag = 0;

            if (s->ps.pps->deblocking_filter_override_enabled_flag)
                deblocking_filter_override_flag = get_bits1(gb);

            if (deblocking_filter_override_flag) {
                sh->disable_deblocking_filter_flag = get_bits1(gb);
                if (!sh->disable_deblocking_filter_flag) {
                    int beta_offset_div2 = get_se_golomb(gb);
                    int tc_offset_div2   = get_se_golomb(gb) ;
                    if (beta_offset_div2 < -6 || beta_offset_div2 > 6 ||
                        tc_offset_div2   < -6 || tc_offset_div2   > 6) {
                        av_log(s->avctx, AV_LOG_ERROR,
                            "Invalid deblock filter offsets: %d, %d\n",
                            beta_offset_div2, tc_offset_div2);
                        return AVERROR_INVALIDDATA;
                    }
                    sh->beta_offset = beta_offset_div2 * 2;
                    sh->tc_offset   =   tc_offset_div2 * 2;
                }
            } else {
                sh->disable_deblocking_filter_flag = s->ps.pps->disable_dbf;
                sh->beta_offset                    = s->ps.pps->beta_offset;
                sh->tc_offset                      = s->ps.pps->tc_offset;
            }
        } else {
            sh->disable_deblocking_filter_flag = 0;
            sh->beta_offset                    = 0;
            sh->tc_offset                      = 0;
        }

        if (s->ps.pps->seq_loop_filter_across_slices_enabled_flag &&
            (sh->slice_sample_adaptive_offset_flag[0] ||
             sh->slice_sample_adaptive_offset_flag[1] ||
             !sh->disable_deblocking_filter_flag)) {
            sh->slice_loop_filter_across_slices_enabled_flag = get_bits1(gb);
        } else {
            sh->slice_loop_filter_across_slices_enabled_flag = s->ps.pps->seq_loop_filter_across_slices_enabled_flag;
        }
    } else if (!s->slice_initialized) {
        av_log(s->avctx, AV_LOG_ERROR, "Independent slice segment missing.\n");
        return AVERROR_INVALIDDATA;
    }

    sh->num_entry_point_offsets = 0;
    if (s->ps.pps->tiles_enabled_flag || s->ps.pps->entropy_coding_sync_enabled_flag) {
        unsigned num_entry_point_offsets = get_ue_golomb_long(gb);
        // It would be possible to bound this tighter but this here is simpler
        if (num_entry_point_offsets > get_bits_left(gb)) {
            av_log(s->avctx, AV_LOG_ERROR, "num_entry_point_offsets %d is invalid\n", num_entry_point_offsets);
            return AVERROR_INVALIDDATA;
        }

        sh->num_entry_point_offsets = num_entry_point_offsets;
        if (sh->num_entry_point_offsets > 0) {
            int offset_len = get_ue_golomb_long(gb) + 1;

            if (offset_len < 1 || offset_len > 32) {
                sh->num_entry_point_offsets = 0;
                av_log(s->avctx, AV_LOG_ERROR, "offset_len %d is invalid\n", offset_len);
                return AVERROR_INVALIDDATA;
            }

            av_freep(&sh->entry_point_offset);
            av_freep(&sh->offset);
            av_freep(&sh->size);
            sh->entry_point_offset = av_malloc_array(sh->num_entry_point_offsets, sizeof(unsigned));
            sh->offset = av_malloc_array(sh->num_entry_point_offsets, sizeof(int));
            sh->size = av_malloc_array(sh->num_entry_point_offsets, sizeof(int));
            if (!sh->entry_point_offset || !sh->offset || !sh->size) {
                sh->num_entry_point_offsets = 0;
                av_log(s->avctx, AV_LOG_ERROR, "Failed to allocate memory\n");
                return AVERROR(ENOMEM);
            }
            for (i = 0; i < sh->num_entry_point_offsets; i++) {
                unsigned val = get_bits_long(gb, offset_len);
                sh->entry_point_offset[i] = val + 1; // +1; // +1 to get the size
            }
            if (s->threads_number > 1 && (s->ps.pps->num_tile_rows > 1 || s->ps.pps->num_tile_columns > 1)) {
                s->enable_parallel_tiles = 0; // TODO: you can enable tiles in parallel here
                s->threads_number = 1;
            } else
                s->enable_parallel_tiles = 0;
        } else
            s->enable_parallel_tiles = 0;
    }

    if (s->ps.pps->slice_header_extension_present_flag) {
        unsigned int length = get_ue_golomb_long(gb);
        if (length*8LL > get_bits_left(gb)) {
            av_log(s->avctx, AV_LOG_ERROR, "too many slice_header_extension_data_bytes\n");
            return AVERROR_INVALIDDATA;
        }
        for (i = 0; i < length; i++)
            skip_bits(gb, 8);  // slice_header_extension_data_byte
    }

    // Inferred parameters
    sh->slice_qp = 26U + s->ps.pps->pic_init_qp_minus26 + sh->slice_qp_delta;
    if (sh->slice_qp > 51 ||
        sh->slice_qp < -s->ps.sps->qp_bd_offset) {
        av_log(s->avctx, AV_LOG_ERROR,
               "The slice_qp %d is outside the valid range "
               "[%d, 51].\n",
               sh->slice_qp,
               -s->ps.sps->qp_bd_offset);
        return AVERROR_INVALIDDATA;
    }

    sh->slice_ctb_addr_rs = sh->slice_segment_addr;

    if (!s->sh.slice_ctb_addr_rs && s->sh.dependent_slice_segment_flag) {
        av_log(s->avctx, AV_LOG_ERROR, "Impossible slice segment.\n");
        return AVERROR_INVALIDDATA;
    }

    if (get_bits_left(gb) < 0) {
        av_log(s->avctx, AV_LOG_ERROR,
               "Overread slice header by %d bits\n", -get_bits_left(gb));
        return AVERROR_INVALIDDATA;
    }

    s->HEVClc->first_qp_group = !s->sh.dependent_slice_segment_flag;

    if (!s->ps.pps->cu_qp_delta_enabled_flag)
        s->HEVClc->qp_y = s->sh.slice_qp;

    s->slice_initialized = 1;
    s->HEVClc->tu.cu_qp_offset_cb = 0;
    s->HEVClc->tu.cu_qp_offset_cr = 0;

    return 0;
}