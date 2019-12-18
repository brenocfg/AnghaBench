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
 int png_colorspace_check_xy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int png_colorspace_set_xy_and_XYZ (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

int /* PRIVATE */
png_colorspace_set_chromaticities(png_const_structrp png_ptr,
    png_colorspacerp colorspace, const png_xy *xy, int preferred)
{
   /* We must check the end points to ensure they are reasonable - in the past
    * color management systems have crashed as a result of getting bogus
    * colorant values, while this isn't the fault of libpng it is the
    * responsibility of libpng because PNG carries the bomb and libpng is in a
    * position to protect against it.
    */
   png_XYZ XYZ;

   switch (png_colorspace_check_xy(&XYZ, xy))
   {
      case 0: /* success */
         return png_colorspace_set_xy_and_XYZ(png_ptr, colorspace, xy, &XYZ,
             preferred);

      case 1:
         /* We can't invert the chromaticities so we can't produce value XYZ
          * values.  Likely as not a color management system will fail too.
          */
         colorspace->flags |= PNG_COLORSPACE_INVALID;
         png_benign_error(png_ptr, "invalid chromaticities");
         break;

      default:
         /* libpng is broken; this should be a warning but if it happens we
          * want error reports so for the moment it is an error.
          */
         colorspace->flags |= PNG_COLORSPACE_INVALID;
         png_error(png_ptr, "internal error checking chromaticities");
   }

   return 0; /* failed */
}