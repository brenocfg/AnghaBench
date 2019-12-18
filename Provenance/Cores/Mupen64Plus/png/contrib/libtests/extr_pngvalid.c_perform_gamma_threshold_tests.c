#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  interlace_type; int /*<<< orphan*/  test_tRNS; int /*<<< orphan*/  test_lbg_gamma_threshold; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 scalar_t__ fail (TYPE_1__*) ; 
 int /*<<< orphan*/  gamma_threshold_test (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 
 scalar_t__ next_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perform_gamma_threshold_tests(png_modifier *pm)
{
   png_byte colour_type = 0;
   png_byte bit_depth = 0;
   unsigned int palette_number = 0;

   /* Don't test more than one instance of each palette - it's pointless, in
    * fact this test is somewhat excessive since libpng doesn't make this
    * decision based on colour type or bit depth!
    *
    * CHANGED: now test two palettes and, as a side effect, images with and
    * without tRNS.
    */
   while (next_format(&colour_type, &bit_depth, &palette_number,
                      pm->test_lbg_gamma_threshold, pm->test_tRNS))
      if (palette_number < 2)
   {
      double test_gamma = 1.0;
      while (test_gamma >= .4)
      {
         /* There's little point testing the interlacing vs non-interlacing,
          * but this can be set from the command line.
          */
         gamma_threshold_test(pm, colour_type, bit_depth, pm->interlace_type,
            test_gamma, 1/test_gamma);
         test_gamma *= .95;
      }

      /* And a special test for sRGB */
      gamma_threshold_test(pm, colour_type, bit_depth, pm->interlace_type,
          .45455, 2.2);

      if (fail(pm))
         return;
   }
}