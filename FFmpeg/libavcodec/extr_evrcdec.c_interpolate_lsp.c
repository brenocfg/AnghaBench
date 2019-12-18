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

/* Variables and functions */
 int /*<<< orphan*/  FILTER_ORDER ; 
 int /*<<< orphan*/  ff_weighted_vector_sumf (float*,float const*,float const*,double,float const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void interpolate_lsp(float *ilsp, const float *lsp,
                            const float *prev, int index)
{
    static const float lsp_interpolation_factors[] = { 0.1667, 0.5, 0.8333 };
    ff_weighted_vector_sumf(ilsp, prev, lsp,
                            1.0 - lsp_interpolation_factors[index],
                            lsp_interpolation_factors[index], FILTER_ORDER);
}