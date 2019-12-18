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
typedef  scalar_t__ png_fixed_point ;

/* Variables and functions */
 scalar_t__ PNG_FP_1 ; 
 scalar_t__ PNG_GAMMA_THRESHOLD_FIXED ; 

int /* PRIVATE */
png_gamma_significant(png_fixed_point gamma_val)
{
   return gamma_val < PNG_FP_1 - PNG_GAMMA_THRESHOLD_FIXED ||
       gamma_val > PNG_FP_1 + PNG_GAMMA_THRESHOLD_FIXED;
}