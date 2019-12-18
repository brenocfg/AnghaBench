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
typedef  float spx_word16_t ;

/* Variables and functions */

__attribute__((used)) static void cubic_coef(spx_word16_t frac, spx_word16_t interp[4])
{
   /* Compute interpolation coefficients. I'm not sure whether this corresponds to cubic interpolation
   but I know it's MMSE-optimal on a sinc */
   interp[0] =  -0.16667f*frac + 0.16667f*frac*frac*frac;
   interp[1] = frac + 0.5f*frac*frac - 0.5f*frac*frac*frac;
   /*interp[2] = 1.f - 0.5f*frac - frac*frac + 0.5f*frac*frac*frac;*/
   interp[3] = -0.33333f*frac + 0.5f*frac*frac - 0.16667f*frac*frac*frac;
   /* Just to make sure we don't have rounding problems */
   interp[2] = 1.-interp[0]-interp[1]-interp[3];
}