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
struct TYPE_3__ {int /*<<< orphan*/  bs_num_noise; int /*<<< orphan*/  bs_df_noise; int /*<<< orphan*/  bs_num_env; int /*<<< orphan*/  bs_df_env; } ;
typedef  int /*<<< orphan*/  SpectralBandReplication ;
typedef  TYPE_1__ SBRData ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits1_vector (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_sbr_dtdf(SpectralBandReplication *sbr, GetBitContext *gb,
                          SBRData *ch_data)
{
    get_bits1_vector(gb, ch_data->bs_df_env,   ch_data->bs_num_env);
    get_bits1_vector(gb, ch_data->bs_df_noise, ch_data->bs_num_noise);
}