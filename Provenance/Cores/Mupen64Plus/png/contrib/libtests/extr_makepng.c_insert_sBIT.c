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
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_3__ {int red; int green; int blue; int gray; int alpha; } ;
typedef  TYPE_1__ png_color_8 ;
typedef  int /*<<< orphan*/ * png_charpp ;

/* Variables and functions */
 int const PNG_COLOR_MASK_ALPHA ; 
 int const PNG_COLOR_MASK_COLOR ; 
 int const PNG_COLOR_MASK_PALETTE ; 
 void* bval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 unsigned int png_get_bit_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int png_get_color_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_sBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
insert_sBIT(png_structp png_ptr, png_infop info_ptr, int nparams,
      png_charpp params)
{
   const int ct = png_get_color_type(png_ptr, info_ptr);
   const int c = (ct & PNG_COLOR_MASK_COLOR ? 3 : 1) +
      (ct & PNG_COLOR_MASK_ALPHA ? 1 : 0);
   const unsigned int maxval =
      ct & PNG_COLOR_MASK_PALETTE ? 8U : png_get_bit_depth(png_ptr, info_ptr);
   png_color_8 sBIT;

   if (nparams != c)
      png_error(png_ptr, "sBIT: incorrect parameter count");

   if (ct & PNG_COLOR_MASK_COLOR)
   {
      sBIT.red = bval(png_ptr, params[0], maxval);
      sBIT.green = bval(png_ptr, params[1], maxval);
      sBIT.blue = bval(png_ptr, params[2], maxval);
      sBIT.gray = 42;
   }

   else
   {
      sBIT.red = sBIT.green = sBIT.blue = 42;
      sBIT.gray = bval(png_ptr, params[0], maxval);
   }

   if (ct & PNG_COLOR_MASK_ALPHA)
      sBIT.alpha = bval(png_ptr, params[nparams-1], maxval);

   else
      sBIT.alpha = 42;

   png_set_sBIT(png_ptr, info_ptr, &sBIT);
}