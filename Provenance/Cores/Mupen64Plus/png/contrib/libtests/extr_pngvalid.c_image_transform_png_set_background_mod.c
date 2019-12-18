#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  this; } ;
typedef  TYPE_1__ transform_display ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_14__ {TYPE_4__* next; } ;
typedef  TYPE_2__ image_transform ;
struct TYPE_15__ {scalar_t__ colour_type; int alphaf; double redf; double greenf; double bluef; double rede; double greene; double bluee; scalar_t__ alphae; int /*<<< orphan*/  blue_sBIT; int /*<<< orphan*/  green_sBIT; int /*<<< orphan*/  red_sBIT; scalar_t__ have_tRNS; } ;
typedef  TYPE_3__ image_pixel ;
struct TYPE_16__ {int /*<<< orphan*/  (* mod ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ;} ;
struct TYPE_12__ {double redf; double greenf; double bluef; double rede; double greene; double bluee; int /*<<< orphan*/  blue_sBIT; int /*<<< orphan*/  green_sBIT; int /*<<< orphan*/  red_sBIT; } ;

/* Variables and functions */
 double DBL_EPSILON ; 
 scalar_t__ PNG_COLOR_TYPE_GRAY ; 
 scalar_t__ PNG_COLOR_TYPE_GRAY_ALPHA ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 scalar_t__ PNG_COLOR_TYPE_RGB ; 
 scalar_t__ PNG_COLOR_TYPE_RGB_ALPHA ; 
 TYPE_11__ data ; 
 int /*<<< orphan*/  image_pixel_add_alpha (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__ const*) ; 

__attribute__((used)) static void
image_transform_png_set_background_mod(const image_transform *this,
    image_pixel *that, png_const_structp pp,
    const transform_display *display)
{
   /* Check for tRNS first: */
   if (that->have_tRNS && that->colour_type != PNG_COLOR_TYPE_PALETTE)
      image_pixel_add_alpha(that, &display->this, 1/*for background*/);

   /* This is only necessary if the alpha value is less than 1. */
   if (that->alphaf < 1)
   {
      /* Now we do the background calculation without any gamma correction. */
      if (that->alphaf <= 0)
      {
         that->redf = data.redf;
         that->greenf = data.greenf;
         that->bluef = data.bluef;

         that->rede = data.rede;
         that->greene = data.greene;
         that->bluee = data.bluee;

         that->red_sBIT= data.red_sBIT;
         that->green_sBIT= data.green_sBIT;
         that->blue_sBIT= data.blue_sBIT;
      }

      else /* 0 < alpha < 1 */
      {
         double alf = 1 - that->alphaf;

         that->redf = that->redf * that->alphaf + data.redf * alf;
         that->rede = that->rede * that->alphaf + data.rede * alf +
            DBL_EPSILON;
         that->greenf = that->greenf * that->alphaf + data.greenf * alf;
         that->greene = that->greene * that->alphaf + data.greene * alf +
            DBL_EPSILON;
         that->bluef = that->bluef * that->alphaf + data.bluef * alf;
         that->bluee = that->bluee * that->alphaf + data.bluee * alf +
            DBL_EPSILON;
      }

      /* Remove the alpha type and set the alpha (not in that order.) */
      that->alphaf = 1;
      that->alphae = 0;
   }

   if (that->colour_type == PNG_COLOR_TYPE_RGB_ALPHA)
      that->colour_type = PNG_COLOR_TYPE_RGB;
   else if (that->colour_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      that->colour_type = PNG_COLOR_TYPE_GRAY;
   /* PNG_COLOR_TYPE_PALETTE is not changed */

   this->next->mod(this->next, that, pp, display);
}