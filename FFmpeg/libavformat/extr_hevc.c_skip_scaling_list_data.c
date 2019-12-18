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
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_se_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skip_scaling_list_data(GetBitContext *gb)
{
    int i, j, k, num_coeffs;

    for (i = 0; i < 4; i++)
        for (j = 0; j < (i == 3 ? 2 : 6); j++)
            if (!get_bits1(gb))         // scaling_list_pred_mode_flag[i][j]
                get_ue_golomb_long(gb); // scaling_list_pred_matrix_id_delta[i][j]
            else {
                num_coeffs = FFMIN(64, 1 << (4 + (i << 1)));

                if (i > 1)
                    get_se_golomb_long(gb); // scaling_list_dc_coef_minus8[i-2][j]

                for (k = 0; k < num_coeffs; k++)
                    get_se_golomb_long(gb); // scaling_list_delta_coef
            }
}