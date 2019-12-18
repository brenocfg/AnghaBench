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
typedef  int png_byte ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int png_get_bit_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ png_get_color_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_sBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
sBIT_error_fn(png_structp pp, png_infop pi)
{
   png_byte bit_depth;
   png_color_8 bad;

   if (png_get_color_type(pp, pi) == PNG_COLOR_TYPE_PALETTE)
      bit_depth = 8;

   else
      bit_depth = png_get_bit_depth(pp, pi);

   /* Now we know the bit depth we can easily generate an invalid sBIT entry */
   bad.red = bad.green = bad.blue = bad.gray = bad.alpha =
      (png_byte)(bit_depth+1);
   png_set_sBIT(pp, pi, &bad);
}