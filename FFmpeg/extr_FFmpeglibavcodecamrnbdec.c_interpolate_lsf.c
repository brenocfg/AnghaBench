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
struct TYPE_3__ {int /*<<< orphan*/  (* weighted_vector_sumf ) (float*,float*,float*,double,double,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ACELPVContext ;

/* Variables and functions */
 int /*<<< orphan*/  LP_FILTER_ORDER ; 
 int /*<<< orphan*/  stub1 (float*,float*,float*,double,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void interpolate_lsf(ACELPVContext *ctx, float lsf_q[4][LP_FILTER_ORDER], float *lsf_new)
{
    int i;

    for (i = 0; i < 4; i++)
        ctx->weighted_vector_sumf(lsf_q[i], lsf_q[3], lsf_new,
                                0.25 * (3 - i), 0.25 * (i + 1),
                                LP_FILTER_ORDER);
}