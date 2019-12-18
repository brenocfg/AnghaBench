#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  png_xy ;
typedef  int /*<<< orphan*/  png_XYZ ;

/* Variables and functions */
 int png_XYZ_from_xy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ png_colorspace_endpoints_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int png_xy_from_XYZ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
png_colorspace_check_xy(png_XYZ *XYZ, const png_xy *xy)
{
   int result;
   png_xy xy_test;

   /* As a side-effect this routine also returns the XYZ endpoints. */
   result = png_XYZ_from_xy(XYZ, xy);
   if (result != 0)
      return result;

   result = png_xy_from_XYZ(&xy_test, XYZ);
   if (result != 0)
      return result;

   if (png_colorspace_endpoints_match(xy, &xy_test,
       5/*actually, the math is pretty accurate*/) != 0)
      return 0;

   /* Too much slip */
   return 1;
}