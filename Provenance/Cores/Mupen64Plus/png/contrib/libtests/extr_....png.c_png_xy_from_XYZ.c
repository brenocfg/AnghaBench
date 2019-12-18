#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  whitey; int /*<<< orphan*/  whitex; int /*<<< orphan*/  bluey; int /*<<< orphan*/  bluex; int /*<<< orphan*/  greeny; int /*<<< orphan*/  greenx; int /*<<< orphan*/  redy; int /*<<< orphan*/  redx; } ;
typedef  TYPE_1__ png_xy ;
typedef  scalar_t__ png_int_32 ;
struct TYPE_6__ {scalar_t__ blue_Y; scalar_t__ blue_X; scalar_t__ blue_Z; scalar_t__ green_Y; scalar_t__ green_X; scalar_t__ green_Z; scalar_t__ red_Y; scalar_t__ red_X; scalar_t__ red_Z; } ;
typedef  TYPE_2__ png_XYZ ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FP_1 ; 
 scalar_t__ png_muldiv (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
png_xy_from_XYZ(png_xy *xy, const png_XYZ *XYZ)
{
   png_int_32 d, dwhite, whiteX, whiteY;

   d = XYZ->red_X + XYZ->red_Y + XYZ->red_Z;
   if (png_muldiv(&xy->redx, XYZ->red_X, PNG_FP_1, d) == 0)
      return 1;
   if (png_muldiv(&xy->redy, XYZ->red_Y, PNG_FP_1, d) == 0)
      return 1;
   dwhite = d;
   whiteX = XYZ->red_X;
   whiteY = XYZ->red_Y;

   d = XYZ->green_X + XYZ->green_Y + XYZ->green_Z;
   if (png_muldiv(&xy->greenx, XYZ->green_X, PNG_FP_1, d) == 0)
      return 1;
   if (png_muldiv(&xy->greeny, XYZ->green_Y, PNG_FP_1, d) == 0)
      return 1;
   dwhite += d;
   whiteX += XYZ->green_X;
   whiteY += XYZ->green_Y;

   d = XYZ->blue_X + XYZ->blue_Y + XYZ->blue_Z;
   if (png_muldiv(&xy->bluex, XYZ->blue_X, PNG_FP_1, d) == 0)
      return 1;
   if (png_muldiv(&xy->bluey, XYZ->blue_Y, PNG_FP_1, d) == 0)
      return 1;
   dwhite += d;
   whiteX += XYZ->blue_X;
   whiteY += XYZ->blue_Y;

   /* The reference white is simply the sum of the end-point (X,Y,Z) vectors,
    * thus:
    */
   if (png_muldiv(&xy->whitex, whiteX, PNG_FP_1, dwhite) == 0)
      return 1;
   if (png_muldiv(&xy->whitey, whiteY, PNG_FP_1, dwhite) == 0)
      return 1;

   return 0;
}