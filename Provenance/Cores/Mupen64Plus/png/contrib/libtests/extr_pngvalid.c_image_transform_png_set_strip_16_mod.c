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
typedef  int /*<<< orphan*/  transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_7__ {TYPE_3__* next; } ;
typedef  TYPE_1__ image_transform ;
struct TYPE_8__ {int bit_depth; int sample_depth; int red_sBIT; int green_sBIT; int blue_sBIT; int alpha_sBIT; double const rede; double const greene; double const bluee; double const alphae; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_9__ {int /*<<< orphan*/  (* mod ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
image_transform_png_set_strip_16_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   if (that->bit_depth == 16)
   {
      that->sample_depth = that->bit_depth = 8;
      if (that->red_sBIT > 8) that->red_sBIT = 8;
      if (that->green_sBIT > 8) that->green_sBIT = 8;
      if (that->blue_sBIT > 8) that->blue_sBIT = 8;
      if (that->alpha_sBIT > 8) that->alpha_sBIT = 8;

      /* Prior to 1.5.4 png_set_strip_16 would use an 'accurate' method if this
       * configuration option is set.  From 1.5.4 the flag is never set and the
       * 'scale' API (above) must be used.
       */
#     ifdef PNG_READ_ACCURATE_SCALE_SUPPORTED
#        if PNG_LIBPNG_VER >= 10504
#           error PNG_READ_ACCURATE_SCALE should not be set
#        endif

         /* The strip 16 algorithm drops the low 8 bits rather than calculating
          * 1/257, so we need to adjust the permitted errors appropriately:
          * Notice that this is only relevant prior to the addition of the
          * png_set_scale_16 API in 1.5.4 (but 1.5.4+ always defines the above!)
          */
         {
            const double d = (255-128.5)/65535;
            that->rede += d;
            that->greene += d;
            that->bluee += d;
            that->alphae += d;
         }
#     endif
   }

   this->next->mod(this->next, that, pp, display);
}