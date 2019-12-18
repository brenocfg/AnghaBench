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
 int png_XYZ_normalize (int /*<<< orphan*/ *) ; 
 int png_colorspace_check_xy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_xy_from_XYZ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
png_colorspace_check_XYZ(png_xy *xy, png_XYZ *XYZ)
{
   int result;
   png_XYZ XYZtemp;

   result = png_XYZ_normalize(XYZ);
   if (result != 0)
      return result;

   result = png_xy_from_XYZ(xy, XYZ);
   if (result != 0)
      return result;

   XYZtemp = *XYZ;
   return png_colorspace_check_xy(&XYZtemp, xy);
}