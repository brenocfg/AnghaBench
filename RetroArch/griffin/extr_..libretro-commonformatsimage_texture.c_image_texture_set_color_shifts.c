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
struct texture_image {scalar_t__ supports_rgba; } ;

/* Variables and functions */

bool image_texture_set_color_shifts(
      unsigned *r_shift, unsigned *g_shift, unsigned *b_shift,
      unsigned *a_shift,
      struct texture_image *out_img
      )
{
   *a_shift             = 24;
   *r_shift             = 16;
   *g_shift             = 8;
   *b_shift             = 0;

   if (out_img->supports_rgba)
   {
      *r_shift = 0;
      *b_shift = 16;
      return true;
   }

   return false;
}