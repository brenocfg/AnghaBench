#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_13__ {TYPE_4__* next; } ;
typedef  TYPE_2__ image_transform ;
struct TYPE_14__ {scalar_t__ colour_type; int bit_depth; int sample_depth; scalar_t__ have_tRNS; } ;
typedef  TYPE_3__ image_pixel ;
struct TYPE_15__ {int /*<<< orphan*/  (* mod ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ;} ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  image_pixel_add_alpha (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  image_pixel_convert_PLTE (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 

__attribute__((used)) static void
image_transform_png_set_expand_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   /* The general expand case depends on what the colour type is: */
   if (that->colour_type == PNG_COLOR_TYPE_PALETTE)
      image_pixel_convert_PLTE(that);
   else if (that->bit_depth < 8) /* grayscale */
      that->sample_depth = that->bit_depth = 8;

   if (that->have_tRNS)
      image_pixel_add_alpha(that, &display->this, 0/*!for background*/);

   this->next->mod(this->next, that, pp, display);
}