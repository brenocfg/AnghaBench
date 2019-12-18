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
struct FuncDef {float oversample; double* table; } ;

/* Variables and functions */
 scalar_t__ floor (float) ; 

__attribute__((used)) static double compute_func(float x, struct FuncDef *func)
{
   float y, frac;
   double interp[4];
   int ind; 
   y = x*func->oversample;
   ind = (int)floor(y);
   frac = (y-ind);
   /* CSE with handle the repeated powers */
   interp[3] =  -0.1666666667*frac + 0.1666666667*(frac*frac*frac);
   interp[2] = frac + 0.5*(frac*frac) - 0.5*(frac*frac*frac);
   /*interp[2] = 1.f - 0.5f*frac - frac*frac + 0.5f*frac*frac*frac;*/
   interp[0] = -0.3333333333*frac + 0.5*(frac*frac) - 0.1666666667*(frac*frac*frac);
   /* Just to make sure we don't have rounding problems */
   interp[1] = 1.f-interp[3]-interp[2]-interp[0];
   
   /*sum = frac*accum[1] + (1-frac)*accum[2];*/
   return interp[0]*func->table[ind] + interp[1]*func->table[ind+1] + interp[2]*func->table[ind+2] + interp[3]*func->table[ind+3];
}