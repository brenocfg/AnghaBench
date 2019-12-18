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
typedef  int png_uint_32 ;
struct TYPE_3__ {int image_h; int cb_row; scalar_t__ cb_image; int /*<<< orphan*/ * image; } ;
typedef  TYPE_1__ png_store ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  int /*<<< orphan*/ * png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static png_bytep
store_image_row(const png_store* ps, png_const_structp pp, int nImage,
   png_uint_32 y)
{
   png_size_t coffset = (nImage * ps->image_h + y) * (ps->cb_row + 5) + 2;

   if (ps->image == NULL)
      png_error(pp, "no allocated image");

   if (coffset + ps->cb_row + 3 > ps->cb_image)
      png_error(pp, "image too small");

   return ps->image + coffset;
}