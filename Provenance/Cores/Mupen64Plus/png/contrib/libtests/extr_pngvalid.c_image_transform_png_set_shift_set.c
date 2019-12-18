#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned int bit_depth; } ;
struct TYPE_11__ {TYPE_1__ this; } ;
typedef  TYPE_2__ transform_display ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  void* png_byte ;
struct TYPE_12__ {TYPE_4__* next; } ;
typedef  TYPE_3__ image_transform ;
struct TYPE_14__ {void* alpha; void* gray; void* blue; void* green; void* red; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* set ) (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_6__ data ; 
 int /*<<< orphan*/  png_set_shift (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ random_mod (unsigned int const) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
image_transform_png_set_shift_set(const image_transform *this,
    transform_display *that, png_structp pp, png_infop pi)
{
   /* Get a random set of shifts.  The shifts need to do something
    * to test the transform, so they are limited to the bit depth
    * of the input image.  Notice that in the following the 'gray'
    * field is randomized independently.  This acts as a check that
    * libpng does use the correct field.
    */
   const unsigned int depth = that->this.bit_depth;

   data.red = (png_byte)/*SAFE*/(random_mod(depth)+1);
   data.green = (png_byte)/*SAFE*/(random_mod(depth)+1);
   data.blue = (png_byte)/*SAFE*/(random_mod(depth)+1);
   data.gray = (png_byte)/*SAFE*/(random_mod(depth)+1);
   data.alpha = (png_byte)/*SAFE*/(random_mod(depth)+1);

   png_set_shift(pp, &data);
   this->next->set(this->next, that, pp, pi);
}