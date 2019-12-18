#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ red; scalar_t__ green; scalar_t__ blue; } ;
struct TYPE_8__ {int /*<<< orphan*/  alpha_sBIT; TYPE_1__ transparent; } ;
typedef  TYPE_2__ standard_display ;
struct TYPE_9__ {scalar_t__ colour_type; int bit_depth; int sample_depth; scalar_t__ red; int alphaf; scalar_t__ green; scalar_t__ blue; int /*<<< orphan*/  alpha_sBIT; scalar_t__ alphae; scalar_t__ have_tRNS; } ;
typedef  TYPE_3__ image_pixel ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int /*<<< orphan*/  image_pixel_convert_PLTE (TYPE_3__*) ; 

__attribute__((used)) static void
image_pixel_add_alpha(image_pixel *this, const standard_display *display,
   int for_background)
{
   if (this->colour_type == PNG_COLOR_TYPE_PALETTE)
      image_pixel_convert_PLTE(this);

   if ((this->colour_type & PNG_COLOR_MASK_ALPHA) == 0)
   {
      if (this->colour_type == PNG_COLOR_TYPE_GRAY)
      {
#        if PNG_LIBPNG_VER < 10700
            if (!for_background && this->bit_depth < 8)
               this->bit_depth = this->sample_depth = 8;
#        endif

         if (this->have_tRNS)
         {
            /* After 1.7 the expansion of bit depth only happens if there is a
             * tRNS chunk to expand at this point.
             */
#           if PNG_LIBPNG_VER >= 10700
               if (!for_background && this->bit_depth < 8)
                  this->bit_depth = this->sample_depth = 8;
#           endif

            this->have_tRNS = 0;

            /* Check the input, original, channel value here against the
             * original tRNS gray chunk valie.
             */
            if (this->red == display->transparent.red)
               this->alphaf = 0;
            else
               this->alphaf = 1;
         }
         else
            this->alphaf = 1;

         this->colour_type = PNG_COLOR_TYPE_GRAY_ALPHA;
      }

      else if (this->colour_type == PNG_COLOR_TYPE_RGB)
      {
         if (this->have_tRNS)
         {
            this->have_tRNS = 0;

            /* Again, check the exact input values, not the current transformed
             * value!
             */
            if (this->red == display->transparent.red &&
               this->green == display->transparent.green &&
               this->blue == display->transparent.blue)
               this->alphaf = 0;
            else
               this->alphaf = 1;
         }
         else
            this->alphaf = 1;

         this->colour_type = PNG_COLOR_TYPE_RGB_ALPHA;
      }

      /* The error in the alpha is zero and the sBIT value comes from the
       * original sBIT data (actually it will always be the original bit depth).
       */
      this->alphae = 0;
      this->alpha_sBIT = display->alpha_sBIT;
   }
}