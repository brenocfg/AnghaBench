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
struct TYPE_8__ {int bit_depth; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_9__ {int /*<<< orphan*/  (* mod ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
image_transform_png_set_packing_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   /* The general expand case depends on what the colour type is,
    * low bit-depth pixel values are unpacked into bytes without
    * scaling, so sample_depth is not changed.
    */
   if (that->bit_depth < 8) /* grayscale or palette */
      that->bit_depth = 8;

   this->next->mod(this->next, that, pp, display);
}