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
struct TYPE_3__ {float tilt_coef; int pitch_lag_int; } ;
typedef  TYPE_1__ AMRWBContext ;

/* Variables and functions */
 int AMRWB_SFR_SIZE ; 

__attribute__((used)) static void pitch_sharpening(AMRWBContext *ctx, float *fixed_vector)
{
    int i;

    /* Tilt part */
    for (i = AMRWB_SFR_SIZE - 1; i != 0; i--)
        fixed_vector[i] -= fixed_vector[i - 1] * ctx->tilt_coef;

    /* Periodicity enhancement part */
    for (i = ctx->pitch_lag_int; i < AMRWB_SFR_SIZE; i++)
        fixed_vector[i] += fixed_vector[i - ctx->pitch_lag_int] * 0.85;
}