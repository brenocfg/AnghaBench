#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_8__ {TYPE_3__* next; } ;
typedef  TYPE_1__ image_transform ;
struct TYPE_9__ {int bit_depth; int colour_type; unsigned int alpha; double alphaf; int alpha_first; scalar_t__ alphae; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_11__ {unsigned int const filler; scalar_t__ flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* mod ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int PNG_COLOR_TYPE_GRAY ; 
 int PNG_COLOR_TYPE_RGB ; 
 scalar_t__ PNG_FILLER_BEFORE ; 
 TYPE_7__ data ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
image_transform_png_set_filler_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   if (that->bit_depth >= 8 &&
       (that->colour_type == PNG_COLOR_TYPE_RGB ||
        that->colour_type == PNG_COLOR_TYPE_GRAY))
   {
      const unsigned int max = (1U << that->bit_depth)-1;
      that->alpha = data.filler & max;
      that->alphaf = ((double)that->alpha) / max;
      that->alphae = 0;

      /* The filler has been stored in the alpha channel, we must record
       * that this has been done for the checking later on, the color
       * type is faked to have an alpha channel, but libpng won't report
       * this; the app has to know the extra channel is there and this
       * was recording in standard_display::filler above.
       */
      that->colour_type |= 4; /* alpha added */
      that->alpha_first = data.flags == PNG_FILLER_BEFORE;
   }

   this->next->mod(this->next, that, pp, display);
}