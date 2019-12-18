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
struct TYPE_3__ {int error_gray_2; int error_gray_4; int error_gray_8; int error_color_8; int error_indexed; int error_gray_16; int error_color_16; } ;
typedef  TYPE_1__ png_modifier ;

/* Variables and functions */

__attribute__((used)) static void
init_gamma_errors(png_modifier *pm)
{
   /* Use -1 to catch tests that were not actually run */
   pm->error_gray_2 = pm->error_gray_4 = pm->error_gray_8 = -1.;
   pm->error_color_8 = -1.;
   pm->error_indexed = -1.;
   pm->error_gray_16 = pm->error_color_16 = -1.;
}