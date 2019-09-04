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
struct TYPE_3__ {scalar_t__ (* dot_productf ) (float*,float*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ CELPMContext ;

/* Variables and functions */
 int /*<<< orphan*/  AMRWB_SFR_SIZE ; 
 scalar_t__ stub1 (float*,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (float*,float*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float voice_factor(float *p_vector, float p_gain,
                          float *f_vector, float f_gain,
                          CELPMContext *ctx)
{
    double p_ener = (double) ctx->dot_productf(p_vector, p_vector,
                                                          AMRWB_SFR_SIZE) *
                    p_gain * p_gain;
    double f_ener = (double) ctx->dot_productf(f_vector, f_vector,
                                                          AMRWB_SFR_SIZE) *
                    f_gain * f_gain;

    return (p_ener - f_ener) / (p_ener + f_ener + 0.01);
}