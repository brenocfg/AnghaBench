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
struct TYPE_9__ {int colour_type; int sig_bits; int /*<<< orphan*/  alpha_sBIT; int /*<<< orphan*/  blue_sBIT; int /*<<< orphan*/  green_sBIT; int /*<<< orphan*/  red_sBIT; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_11__ {int /*<<< orphan*/  alpha; int /*<<< orphan*/  gray; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* mod ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int PNG_COLOR_TYPE_PALETTE ; 
 TYPE_7__ data ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
image_transform_png_set_shift_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   /* Copy the correct values into the sBIT fields, libpng does not do
    * anything to palette data:
    */
   if (that->colour_type != PNG_COLOR_TYPE_PALETTE)
   {
       that->sig_bits = 1;

       /* The sBIT fields are reset to the values previously sent to
        * png_set_shift according to the colour type.
        * does.
        */
       if (that->colour_type & 2) /* RGB channels */
       {
          that->red_sBIT = data.red;
          that->green_sBIT = data.green;
          that->blue_sBIT = data.blue;
       }

       else /* One grey channel */
          that->red_sBIT = that->green_sBIT = that->blue_sBIT = data.gray;

       that->alpha_sBIT = data.alpha;
   }

   this->next->mod(this->next, that, pp, display);
}