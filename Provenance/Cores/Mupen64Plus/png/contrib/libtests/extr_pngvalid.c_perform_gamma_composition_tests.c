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
struct TYPE_5__ {unsigned int ngamma_tests; int* gammas; int /*<<< orphan*/  use_input_precision; int /*<<< orphan*/  interlace_type; int /*<<< orphan*/  test_tRNS; int /*<<< orphan*/  test_lbg_gamma_composition; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int png_byte ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 scalar_t__ fail (TYPE_1__*) ; 
 int /*<<< orphan*/  gamma_composition_test (TYPE_1__*,int,int,unsigned int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ next_format (int*,int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perform_gamma_composition_tests(png_modifier *pm, int do_background,
   int expand_16)
{
   png_byte colour_type = 0;
   png_byte bit_depth = 0;
   unsigned int palette_number = 0;

   /* Skip the non-alpha cases - there is no setting of a transparency colour at
    * present.
    *
    * TODO: incorrect; the palette case sets tRNS and, now RGB and gray do,
    * however the palette case fails miserably so is commented out below.
    */
   while (next_format(&colour_type, &bit_depth, &palette_number,
                      pm->test_lbg_gamma_composition, pm->test_tRNS))
      if ((colour_type & PNG_COLOR_MASK_ALPHA) != 0
#if 0 /* TODO: FIXME */
          /*TODO: FIXME: this should work */
          || colour_type == 3
#endif
          || (colour_type != 3 && palette_number != 0))
   {
      unsigned int i, j;

      /* Don't skip the i==j case here - it's relevant. */
      for (i=0; i<pm->ngamma_tests; ++i) for (j=0; j<pm->ngamma_tests; ++j)
      {
         gamma_composition_test(pm, colour_type, bit_depth, palette_number,
            pm->interlace_type, 1/pm->gammas[i], pm->gammas[j],
            pm->use_input_precision, do_background, expand_16);

         if (fail(pm))
            return;
      }
   }
}