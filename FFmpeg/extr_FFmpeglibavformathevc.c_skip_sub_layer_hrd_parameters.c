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
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skip_sub_layer_hrd_parameters(GetBitContext *gb,
                                          unsigned int cpb_cnt_minus1,
                                          uint8_t sub_pic_hrd_params_present_flag)
{
    unsigned int i;

    for (i = 0; i <= cpb_cnt_minus1; i++) {
        get_ue_golomb_long(gb); // bit_rate_value_minus1
        get_ue_golomb_long(gb); // cpb_size_value_minus1

        if (sub_pic_hrd_params_present_flag) {
            get_ue_golomb_long(gb); // cpb_size_du_value_minus1
            get_ue_golomb_long(gb); // bit_rate_du_value_minus1
        }

        skip_bits1(gb); // cbr_flag
    }
}