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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int level; int tier; void* profile; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AV1SequenceParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AV1_OBU_SEQUENCE_HEADER ; 
 int AVERROR_INVALIDDATA ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int get_obu_bit_length (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_color_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uvlc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_sequence_header(AV1SequenceParameters *seq_params, const uint8_t *buf, int size)
{
    GetBitContext gb;
    int reduced_still_picture_header;
    int frame_width_bits_minus_1, frame_height_bits_minus_1;
    int size_bits, ret;

    size_bits = get_obu_bit_length(buf, size, AV1_OBU_SEQUENCE_HEADER);
    if (size_bits < 0)
        return size_bits;

    ret = init_get_bits(&gb, buf, size_bits);
    if (ret < 0)
        return ret;

    memset(seq_params, 0, sizeof(*seq_params));

    seq_params->profile = get_bits(&gb, 3);

    skip_bits1(&gb); // still_picture
    reduced_still_picture_header = get_bits1(&gb);

    if (reduced_still_picture_header) {
        seq_params->level = get_bits(&gb, 5);
        seq_params->tier = 0;
    } else {
        int initial_display_delay_present_flag, operating_points_cnt_minus_1;
        int decoder_model_info_present_flag, buffer_delay_length_minus_1;

        if (get_bits1(&gb)) { // timing_info_present_flag
            skip_bits_long(&gb, 32); // num_units_in_display_tick
            skip_bits_long(&gb, 32); // time_scale

            if (get_bits1(&gb)) // equal_picture_interval
                uvlc(&gb); // num_ticks_per_picture_minus_1

            decoder_model_info_present_flag = get_bits1(&gb);
            if (decoder_model_info_present_flag) {
                buffer_delay_length_minus_1 = get_bits(&gb, 5);
                skip_bits_long(&gb, 32); // num_units_in_decoding_tick
                skip_bits(&gb, 10); // buffer_removal_time_length_minus_1 (5)
                                    // frame_presentation_time_length_minus_1 (5)
            }
        } else
            decoder_model_info_present_flag = 0;

        initial_display_delay_present_flag = get_bits1(&gb);

        operating_points_cnt_minus_1 = get_bits(&gb, 5);
        for (int i = 0; i <= operating_points_cnt_minus_1; i++) {
            int seq_level_idx, seq_tier;

            skip_bits(&gb, 12); // operating_point_idc
            seq_level_idx = get_bits(&gb, 5);

            if (seq_level_idx > 7)
                seq_tier = get_bits1(&gb);
            else
                seq_tier = 0;

            if (decoder_model_info_present_flag) {
                if (get_bits1(&gb)) { // decoder_model_present_for_this_op
                    skip_bits_long(&gb, buffer_delay_length_minus_1 + 1); // decoder_buffer_delay
                    skip_bits_long(&gb, buffer_delay_length_minus_1 + 1); // encoder_buffer_delay
                    skip_bits1(&gb); // low_delay_mode_flag
                }
            }

            if (initial_display_delay_present_flag) {
                if (get_bits1(&gb)) // initial_display_delay_present_for_this_op
                    skip_bits(&gb, 4); // initial_display_delay_minus_1
            }

            if (i == 0) {
               seq_params->level = seq_level_idx;
               seq_params->tier = seq_tier;
            }
        }
    }

    frame_width_bits_minus_1  = get_bits(&gb, 4);
    frame_height_bits_minus_1 = get_bits(&gb, 4);

    skip_bits(&gb, frame_width_bits_minus_1 + 1); // max_frame_width_minus_1
    skip_bits(&gb, frame_height_bits_minus_1 + 1); // max_frame_height_minus_1

    if (!reduced_still_picture_header) {
        if (get_bits1(&gb)) // frame_id_numbers_present_flag
            skip_bits(&gb, 7); // delta_frame_id_length_minus_2 (4), additional_frame_id_length_minus_1 (3)
    }

    skip_bits(&gb, 3); // use_128x128_superblock (1), enable_filter_intra (1), enable_intra_edge_filter (1)

    if (!reduced_still_picture_header) {
        int enable_order_hint, seq_force_screen_content_tools;

        skip_bits(&gb, 4); // enable_intraintra_compound (1), enable_masked_compound (1)
                           // enable_warped_motion (1), enable_dual_filter (1)

        enable_order_hint = get_bits1(&gb);
        if (enable_order_hint)
            skip_bits(&gb, 2); // enable_jnt_comp (1), enable_ref_frame_mvs (1)

        if (get_bits1(&gb)) // seq_choose_screen_content_tools
            seq_force_screen_content_tools = 2;
        else
            seq_force_screen_content_tools = get_bits1(&gb);

        if (seq_force_screen_content_tools) {
            if (!get_bits1(&gb)) // seq_choose_integer_mv
                skip_bits1(&gb); // seq_force_integer_mv
        }

        if (enable_order_hint)
            skip_bits(&gb, 3); // order_hint_bits_minus_1
    }

    skip_bits(&gb, 3); // enable_superres (1), enable_cdef (1), enable_restoration (1)

    parse_color_config(seq_params, &gb);

    skip_bits1(&gb); // film_grain_params_present

    if (get_bits_left(&gb))
        return AVERROR_INVALIDDATA;

    return 0;
}