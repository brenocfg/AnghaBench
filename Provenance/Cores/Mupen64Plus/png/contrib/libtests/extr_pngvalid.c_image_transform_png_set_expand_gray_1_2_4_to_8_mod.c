#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_9__ {TYPE_3__* next; } ;
typedef  TYPE_1__ image_transform ;
struct TYPE_10__ {scalar_t__ colour_type; int bit_depth; int sample_depth; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_11__ {int /*<<< orphan*/  (* mod ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_GRAY ; 
 int /*<<< orphan*/  image_transform_png_set_expand_mod (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
image_transform_png_set_expand_gray_1_2_4_to_8_mod(
    const image_transform *this, image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
#if PNG_LIBPNG_VER < 10700
   image_transform_png_set_expand_mod(this, that, pp, display);
#else
   /* Only expand grayscale of bit depth less than 8: */
   if (that->colour_type == PNG_COLOR_TYPE_GRAY &&
       that->bit_depth < 8)
      that->sample_depth = that->bit_depth = 8;

   this->next->mod(this->next, that, pp, display);
#endif /* 1.7 or later */
}