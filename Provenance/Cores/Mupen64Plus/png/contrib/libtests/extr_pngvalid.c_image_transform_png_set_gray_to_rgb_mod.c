#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_12__ {TYPE_4__* next; } ;
typedef  TYPE_2__ image_transform ;
struct TYPE_13__ {int colour_type; int bit_depth; int sample_depth; scalar_t__ have_tRNS; } ;
typedef  TYPE_3__ image_pixel ;
struct TYPE_14__ {int /*<<< orphan*/  (* mod ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ;} ;

/* Variables and functions */
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int PNG_COLOR_TYPE_RGB ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int /*<<< orphan*/  image_pixel_add_alpha (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 

__attribute__((used)) static void
image_transform_png_set_gray_to_rgb_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   /* NOTE: we can actually pend the tRNS processing at this point because we
    * can correctly recognize the original pixel value even though we have
    * mapped the one gray channel to the three RGB ones, but in fact libpng
    * doesn't do this, so we don't either.
    */
   if ((that->colour_type & PNG_COLOR_MASK_COLOR) == 0 && that->have_tRNS)
      image_pixel_add_alpha(that, &display->this, 0/*!for background*/);

   /* Simply expand the bit depth and alter the colour type as required. */
   if (that->colour_type == PNG_COLOR_TYPE_GRAY)
   {
      /* RGB images have a bit depth at least equal to '8' */
      if (that->bit_depth < 8)
         that->sample_depth = that->bit_depth = 8;

      /* And just changing the colour type works here because the green and blue
       * channels are being maintained in lock-step with the red/gray:
       */
      that->colour_type = PNG_COLOR_TYPE_RGB;
   }

   else if (that->colour_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      that->colour_type = PNG_COLOR_TYPE_RGB_ALPHA;

   this->next->mod(this->next, that, pp, display);
}