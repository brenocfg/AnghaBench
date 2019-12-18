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
typedef  scalar_t__ png_uint_32 ;
struct TYPE_3__ {int* image; size_t cb_image; int cb_row; scalar_t__ image_h; } ;
typedef  TYPE_1__ png_store ;
typedef  int png_size_t ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  int* png_const_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
store_image_check(const png_store* ps, png_const_structp pp, int iImage)
{
   png_const_bytep image = ps->image;

   if (image[-1] != 0xed || image[ps->cb_image] != 0xfe)
      png_error(pp, "image overwrite");
   else
   {
      png_size_t cbRow = ps->cb_row;
      png_uint_32 rows = ps->image_h;

      image += iImage * (cbRow+5) * ps->image_h;

      image += 2; /* skip image first row markers */

      for (; rows > 0; --rows)
      {
         if (image[-2] != 190 || image[-1] != 239)
            png_error(pp, "row start overwritten");

         if (image[cbRow] != 222 || image[cbRow+1] != 173 ||
            image[cbRow+2] != 17)
            png_error(pp, "row end overwritten");

         image += cbRow+5;
      }
   }
}