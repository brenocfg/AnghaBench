#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  min_spatial_segmentation_idc; } ;
typedef  TYPE_1__ HEVCDecoderConfigurationRecord ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,unsigned int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_hrd_parameters (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  skip_timing_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hvcc_parse_vui(GetBitContext *gb,
                           HEVCDecoderConfigurationRecord *hvcc,
                           unsigned int max_sub_layers_minus1)
{
    unsigned int min_spatial_segmentation_idc;

    if (get_bits1(gb))              // aspect_ratio_info_present_flag
        if (get_bits(gb, 8) == 255) // aspect_ratio_idc
            skip_bits_long(gb, 32); // sar_width u(16), sar_height u(16)

    if (get_bits1(gb))  // overscan_info_present_flag
        skip_bits1(gb); // overscan_appropriate_flag

    if (get_bits1(gb)) {  // video_signal_type_present_flag
        skip_bits(gb, 4); // video_format u(3), video_full_range_flag u(1)

        if (get_bits1(gb)) // colour_description_present_flag
            /*
             * colour_primaries         u(8)
             * transfer_characteristics u(8)
             * matrix_coeffs            u(8)
             */
            skip_bits(gb, 24);
    }

    if (get_bits1(gb)) {        // chroma_loc_info_present_flag
        get_ue_golomb_long(gb); // chroma_sample_loc_type_top_field
        get_ue_golomb_long(gb); // chroma_sample_loc_type_bottom_field
    }

    /*
     * neutral_chroma_indication_flag u(1)
     * field_seq_flag                 u(1)
     * frame_field_info_present_flag  u(1)
     */
    skip_bits(gb, 3);

    if (get_bits1(gb)) {        // default_display_window_flag
        get_ue_golomb_long(gb); // def_disp_win_left_offset
        get_ue_golomb_long(gb); // def_disp_win_right_offset
        get_ue_golomb_long(gb); // def_disp_win_top_offset
        get_ue_golomb_long(gb); // def_disp_win_bottom_offset
    }

    if (get_bits1(gb)) { // vui_timing_info_present_flag
        skip_timing_info(gb);

        if (get_bits1(gb)) // vui_hrd_parameters_present_flag
            skip_hrd_parameters(gb, 1, max_sub_layers_minus1);
    }

    if (get_bits1(gb)) { // bitstream_restriction_flag
        /*
         * tiles_fixed_structure_flag              u(1)
         * motion_vectors_over_pic_boundaries_flag u(1)
         * restricted_ref_pic_lists_flag           u(1)
         */
        skip_bits(gb, 3);

        min_spatial_segmentation_idc = get_ue_golomb_long(gb);

        /*
         * unsigned int(12) min_spatial_segmentation_idc;
         *
         * The min_spatial_segmentation_idc indication must indicate a level of
         * spatial segmentation equal to or less than the lowest level of
         * spatial segmentation indicated in all the parameter sets.
         */
        hvcc->min_spatial_segmentation_idc = FFMIN(hvcc->min_spatial_segmentation_idc,
                                                   min_spatial_segmentation_idc);

        get_ue_golomb_long(gb); // max_bytes_per_pic_denom
        get_ue_golomb_long(gb); // max_bits_per_min_cu_denom
        get_ue_golomb_long(gb); // log2_max_mv_length_horizontal
        get_ue_golomb_long(gb); // log2_max_mv_length_vertical
    }
}