#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_xy ;
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  TYPE_1__* png_colorspacerp ;
typedef  int /*<<< orphan*/  png_XYZ ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_COLORSPACE_INVALID ; 
 int /*<<< orphan*/  png_benign_error (int /*<<< orphan*/ ,char*) ; 
 int png_colorspace_check_XYZ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_colorspace_set_xy_and_XYZ (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

int /* PRIVATE */
png_colorspace_set_endpoints(png_const_structrp png_ptr,
    png_colorspacerp colorspace, const png_XYZ *XYZ_in, int preferred)
{
   png_XYZ XYZ = *XYZ_in;
   png_xy xy;

   switch (png_colorspace_check_XYZ(&xy, &XYZ))
   {
      case 0:
         return png_colorspace_set_xy_and_XYZ(png_ptr, colorspace, &xy, &XYZ,
             preferred);

      case 1:
         /* End points are invalid. */
         colorspace->flags |= PNG_COLORSPACE_INVALID;
         png_benign_error(png_ptr, "invalid end points");
         break;

      default:
         colorspace->flags |= PNG_COLORSPACE_INVALID;
         png_error(png_ptr, "internal error checking chromaticities");
   }

   return 0; /* failed */
}