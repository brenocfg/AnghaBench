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
struct TYPE_5__ {int sbitlow; unsigned int ngamma_tests; int* gammas; int /*<<< orphan*/  use_input_precision_sbit; int /*<<< orphan*/  interlace_type; int /*<<< orphan*/  test_tRNS; int /*<<< orphan*/  test_lbg_gamma_sbit; } ;
typedef  TYPE_1__ png_modifier ;
typedef  int png_byte ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 int READ_BDHI ; 
 scalar_t__ fail (TYPE_1__*) ; 
 int /*<<< orphan*/  gamma_transform_test (TYPE_1__*,int,int,unsigned int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ next_format (int*,int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perform_gamma_sbit_tests(png_modifier *pm)
{
   png_byte sbit;

   /* The only interesting cases are colour and grayscale, alpha is ignored here
    * for overall speed.  Only bit depths where sbit is less than the bit depth
    * are tested.
    */
   for (sbit=pm->sbitlow; sbit<(1<<READ_BDHI); ++sbit)
   {
      png_byte colour_type = 0, bit_depth = 0;
      unsigned int npalette = 0;

      while (next_format(&colour_type, &bit_depth, &npalette,
                         pm->test_lbg_gamma_sbit, pm->test_tRNS))
         if ((colour_type & PNG_COLOR_MASK_ALPHA) == 0 &&
            ((colour_type == 3 && sbit < 8) ||
            (colour_type != 3 && sbit < bit_depth)))
      {
         unsigned int i;

         for (i=0; i<pm->ngamma_tests; ++i)
         {
            unsigned int j;

            for (j=0; j<pm->ngamma_tests; ++j) if (i != j)
            {
               gamma_transform_test(pm, colour_type, bit_depth, npalette,
                  pm->interlace_type, 1/pm->gammas[i], pm->gammas[j],
                  sbit, pm->use_input_precision_sbit, 0 /*scale16*/);

               if (fail(pm))
                  return;
            }
         }
      }
   }
}