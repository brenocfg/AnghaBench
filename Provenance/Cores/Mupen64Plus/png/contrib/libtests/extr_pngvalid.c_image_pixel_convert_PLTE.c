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
struct TYPE_3__ {scalar_t__ colour_type; int bit_depth; scalar_t__ have_tRNS; } ;
typedef  TYPE_1__ image_pixel ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 scalar_t__ PNG_COLOR_TYPE_RGB ; 
 scalar_t__ PNG_COLOR_TYPE_RGB_ALPHA ; 

__attribute__((used)) static void
image_pixel_convert_PLTE(image_pixel *this)
{
   if (this->colour_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (this->have_tRNS)
      {
         this->colour_type = PNG_COLOR_TYPE_RGB_ALPHA;
         this->have_tRNS = 0;
      }
      else
         this->colour_type = PNG_COLOR_TYPE_RGB;

      /* The bit depth of the row changes at this point too (notice that this is
       * the row format, not the sample depth, which is separate.)
       */
      this->bit_depth = 8;
   }
}