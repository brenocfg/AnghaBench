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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_sublayer_hrd(GetBitContext *gb, unsigned int nb_cpb,
                                int subpic_params_present)
{
    int i;

    for (i = 0; i < nb_cpb; i++) {
        get_ue_golomb_long(gb); // bit_rate_value_minus1
        get_ue_golomb_long(gb); // cpb_size_value_minus1

        if (subpic_params_present) {
            get_ue_golomb_long(gb); // cpb_size_du_value_minus1
            get_ue_golomb_long(gb); // bit_rate_du_value_minus1
        }
        skip_bits1(gb); // cbr_flag
    }
}