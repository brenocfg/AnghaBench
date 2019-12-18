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
typedef  int /*<<< orphan*/  png_fixed_point ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FP_1 ; 
 scalar_t__ png_gamma_significant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_muldiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int /* PRIVATE */
png_gamma_threshold(png_fixed_point screen_gamma, png_fixed_point file_gamma)
{
   /* PNG_GAMMA_THRESHOLD is the threshold for performing gamma
    * correction as a difference of the overall transform from 1.0
    *
    * We want to compare the threshold with s*f - 1, if we get
    * overflow here it is because of wacky gamma values so we
    * turn on processing anyway.
    */
   png_fixed_point gtest;
   return !png_muldiv(&gtest, screen_gamma, file_gamma, PNG_FP_1) ||
       png_gamma_significant(gtest);
}