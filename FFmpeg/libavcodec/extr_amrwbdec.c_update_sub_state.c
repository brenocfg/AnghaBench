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
struct TYPE_3__ {int /*<<< orphan*/ * samples_hb; int /*<<< orphan*/ * samples_up; int /*<<< orphan*/ * samples_az; int /*<<< orphan*/ * fixed_gain; int /*<<< orphan*/ * pitch_gain; int /*<<< orphan*/ * excitation_buf; } ;
typedef  TYPE_1__ AMRWBContext ;

/* Variables and functions */
 int AMRWB_P_DELAY_MAX ; 
 size_t AMRWB_SFR_SIZE ; 
 size_t AMRWB_SFR_SIZE_16k ; 
 int LP_ORDER ; 
 int LP_ORDER_16k ; 
 int UPS_MEM_SIZE ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void update_sub_state(AMRWBContext *ctx)
{
    memmove(&ctx->excitation_buf[0], &ctx->excitation_buf[AMRWB_SFR_SIZE],
            (AMRWB_P_DELAY_MAX + LP_ORDER + 1) * sizeof(float));

    memmove(&ctx->pitch_gain[1], &ctx->pitch_gain[0], 5 * sizeof(float));
    memmove(&ctx->fixed_gain[1], &ctx->fixed_gain[0], 1 * sizeof(float));

    memmove(&ctx->samples_az[0], &ctx->samples_az[AMRWB_SFR_SIZE],
            LP_ORDER * sizeof(float));
    memmove(&ctx->samples_up[0], &ctx->samples_up[AMRWB_SFR_SIZE],
            UPS_MEM_SIZE * sizeof(float));
    memmove(&ctx->samples_hb[0], &ctx->samples_hb[AMRWB_SFR_SIZE_16k],
            LP_ORDER_16k * sizeof(float));
}