#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_sub_layer_hrd_parameters (int /*<<< orphan*/ *,unsigned int,scalar_t__) ; 

__attribute__((used)) static int skip_hrd_parameters(GetBitContext *gb, uint8_t cprms_present_flag,
                                unsigned int max_sub_layers_minus1)
{
    unsigned int i;
    uint8_t sub_pic_hrd_params_present_flag = 0;
    uint8_t nal_hrd_parameters_present_flag = 0;
    uint8_t vcl_hrd_parameters_present_flag = 0;

    if (cprms_present_flag) {
        nal_hrd_parameters_present_flag = get_bits1(gb);
        vcl_hrd_parameters_present_flag = get_bits1(gb);

        if (nal_hrd_parameters_present_flag ||
            vcl_hrd_parameters_present_flag) {
            sub_pic_hrd_params_present_flag = get_bits1(gb);

            if (sub_pic_hrd_params_present_flag)
                /*
                 * tick_divisor_minus2                          u(8)
                 * du_cpb_removal_delay_increment_length_minus1 u(5)
                 * sub_pic_cpb_params_in_pic_timing_sei_flag    u(1)
                 * dpb_output_delay_du_length_minus1            u(5)
                 */
                skip_bits(gb, 19);

            /*
             * bit_rate_scale u(4)
             * cpb_size_scale u(4)
             */
            skip_bits(gb, 8);

            if (sub_pic_hrd_params_present_flag)
                skip_bits(gb, 4); // cpb_size_du_scale

            /*
             * initial_cpb_removal_delay_length_minus1 u(5)
             * au_cpb_removal_delay_length_minus1      u(5)
             * dpb_output_delay_length_minus1          u(5)
             */
            skip_bits(gb, 15);
        }
    }

    for (i = 0; i <= max_sub_layers_minus1; i++) {
        unsigned int cpb_cnt_minus1            = 0;
        uint8_t low_delay_hrd_flag             = 0;
        uint8_t fixed_pic_rate_within_cvs_flag = 0;
        uint8_t fixed_pic_rate_general_flag    = get_bits1(gb);

        if (!fixed_pic_rate_general_flag)
            fixed_pic_rate_within_cvs_flag = get_bits1(gb);

        if (fixed_pic_rate_within_cvs_flag)
            get_ue_golomb_long(gb); // elemental_duration_in_tc_minus1
        else
            low_delay_hrd_flag = get_bits1(gb);

        if (!low_delay_hrd_flag) {
            cpb_cnt_minus1 = get_ue_golomb_long(gb);
            if (cpb_cnt_minus1 > 31)
                return AVERROR_INVALIDDATA;
        }

        if (nal_hrd_parameters_present_flag)
            skip_sub_layer_hrd_parameters(gb, cpb_cnt_minus1,
                                          sub_pic_hrd_params_present_flag);

        if (vcl_hrd_parameters_present_flag)
            skip_sub_layer_hrd_parameters(gb, cpb_cnt_minus1,
                                          sub_pic_hrd_params_present_flag);
    }

    return 0;
}