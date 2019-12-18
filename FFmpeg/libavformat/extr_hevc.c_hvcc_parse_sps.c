#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int chromaFormat; void* bitDepthChromaMinus8; void* bitDepthLumaMinus8; scalar_t__ temporalIdNested; int /*<<< orphan*/  numTemporalLayers; } ;
typedef  TYPE_1__ HEVCDecoderConfigurationRecord ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,unsigned int) ; 
 int FFMIN (unsigned int,int) ; 
 int HEVC_MAX_SHORT_TERM_REF_PIC_SETS ; 
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hvcc_parse_ptl (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  hvcc_parse_vui (int /*<<< orphan*/ *,TYPE_1__*,unsigned int) ; 
 int parse_rps (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_scaling_list_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_sub_layer_ordering_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvcc_parse_sps(GetBitContext *gb,
                          HEVCDecoderConfigurationRecord *hvcc)
{
    unsigned int i, sps_max_sub_layers_minus1, log2_max_pic_order_cnt_lsb_minus4;
    unsigned int num_short_term_ref_pic_sets, num_delta_pocs[HEVC_MAX_SHORT_TERM_REF_PIC_SETS];

    skip_bits(gb, 4); // sps_video_parameter_set_id

    sps_max_sub_layers_minus1 = get_bits (gb, 3);

    /*
     * numTemporalLayers greater than 1 indicates that the stream to which this
     * configuration record applies is temporally scalable and the contained
     * number of temporal layers (also referred to as temporal sub-layer or
     * sub-layer in ISO/IEC 23008-2) is equal to numTemporalLayers. Value 1
     * indicates that the stream is not temporally scalable. Value 0 indicates
     * that it is unknown whether the stream is temporally scalable.
     */
    hvcc->numTemporalLayers = FFMAX(hvcc->numTemporalLayers,
                                    sps_max_sub_layers_minus1 + 1);

    hvcc->temporalIdNested = get_bits1(gb);

    hvcc_parse_ptl(gb, hvcc, sps_max_sub_layers_minus1);

    get_ue_golomb_long(gb); // sps_seq_parameter_set_id

    hvcc->chromaFormat = get_ue_golomb_long(gb);

    if (hvcc->chromaFormat == 3)
        skip_bits1(gb); // separate_colour_plane_flag

    get_ue_golomb_long(gb); // pic_width_in_luma_samples
    get_ue_golomb_long(gb); // pic_height_in_luma_samples

    if (get_bits1(gb)) {        // conformance_window_flag
        get_ue_golomb_long(gb); // conf_win_left_offset
        get_ue_golomb_long(gb); // conf_win_right_offset
        get_ue_golomb_long(gb); // conf_win_top_offset
        get_ue_golomb_long(gb); // conf_win_bottom_offset
    }

    hvcc->bitDepthLumaMinus8          = get_ue_golomb_long(gb);
    hvcc->bitDepthChromaMinus8        = get_ue_golomb_long(gb);
    log2_max_pic_order_cnt_lsb_minus4 = get_ue_golomb_long(gb);

    /* sps_sub_layer_ordering_info_present_flag */
    i = get_bits1(gb) ? 0 : sps_max_sub_layers_minus1;
    for (; i <= sps_max_sub_layers_minus1; i++)
        skip_sub_layer_ordering_info(gb);

    get_ue_golomb_long(gb); // log2_min_luma_coding_block_size_minus3
    get_ue_golomb_long(gb); // log2_diff_max_min_luma_coding_block_size
    get_ue_golomb_long(gb); // log2_min_transform_block_size_minus2
    get_ue_golomb_long(gb); // log2_diff_max_min_transform_block_size
    get_ue_golomb_long(gb); // max_transform_hierarchy_depth_inter
    get_ue_golomb_long(gb); // max_transform_hierarchy_depth_intra

    if (get_bits1(gb) && // scaling_list_enabled_flag
        get_bits1(gb))   // sps_scaling_list_data_present_flag
        skip_scaling_list_data(gb);

    skip_bits1(gb); // amp_enabled_flag
    skip_bits1(gb); // sample_adaptive_offset_enabled_flag

    if (get_bits1(gb)) {           // pcm_enabled_flag
        skip_bits         (gb, 4); // pcm_sample_bit_depth_luma_minus1
        skip_bits         (gb, 4); // pcm_sample_bit_depth_chroma_minus1
        get_ue_golomb_long(gb);    // log2_min_pcm_luma_coding_block_size_minus3
        get_ue_golomb_long(gb);    // log2_diff_max_min_pcm_luma_coding_block_size
        skip_bits1        (gb);    // pcm_loop_filter_disabled_flag
    }

    num_short_term_ref_pic_sets = get_ue_golomb_long(gb);
    if (num_short_term_ref_pic_sets > HEVC_MAX_SHORT_TERM_REF_PIC_SETS)
        return AVERROR_INVALIDDATA;

    for (i = 0; i < num_short_term_ref_pic_sets; i++) {
        int ret = parse_rps(gb, i, num_short_term_ref_pic_sets, num_delta_pocs);
        if (ret < 0)
            return ret;
    }

    if (get_bits1(gb)) {                               // long_term_ref_pics_present_flag
        unsigned num_long_term_ref_pics_sps = get_ue_golomb_long(gb);
        if (num_long_term_ref_pics_sps > 31U)
            return AVERROR_INVALIDDATA;
        for (i = 0; i < num_long_term_ref_pics_sps; i++) { // num_long_term_ref_pics_sps
            int len = FFMIN(log2_max_pic_order_cnt_lsb_minus4 + 4, 16);
            skip_bits (gb, len); // lt_ref_pic_poc_lsb_sps[i]
            skip_bits1(gb);      // used_by_curr_pic_lt_sps_flag[i]
        }
    }

    skip_bits1(gb); // sps_temporal_mvp_enabled_flag
    skip_bits1(gb); // strong_intra_smoothing_enabled_flag

    if (get_bits1(gb)) // vui_parameters_present_flag
        hvcc_parse_vui(gb, hvcc, sps_max_sub_layers_minus1);

    /* nothing useful for hvcC past this point */
    return 0;
}