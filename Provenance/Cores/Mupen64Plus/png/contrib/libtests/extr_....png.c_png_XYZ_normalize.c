#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int png_int_32 ;
struct TYPE_3__ {scalar_t__ red_Y; scalar_t__ green_Y; scalar_t__ blue_Y; scalar_t__ red_X; scalar_t__ green_X; scalar_t__ blue_X; scalar_t__ red_Z; scalar_t__ green_Z; scalar_t__ blue_Z; } ;
typedef  TYPE_1__ png_XYZ ;

/* Variables and functions */
 int PNG_FP_1 ; 
 scalar_t__ png_muldiv (int*,int,int,int) ; 

__attribute__((used)) static int
png_XYZ_normalize(png_XYZ *XYZ)
{
   png_int_32 Y;

   if (XYZ->red_Y < 0 || XYZ->green_Y < 0 || XYZ->blue_Y < 0 ||
      XYZ->red_X < 0 || XYZ->green_X < 0 || XYZ->blue_X < 0 ||
      XYZ->red_Z < 0 || XYZ->green_Z < 0 || XYZ->blue_Z < 0)
      return 1;

   /* Normalize by scaling so the sum of the end-point Y values is PNG_FP_1.
    * IMPLEMENTATION NOTE: ANSI requires signed overflow not to occur, therefore
    * relying on addition of two positive values producing a negative one is not
    * safe.
    */
   Y = XYZ->red_Y;
   if (0x7fffffff - Y < XYZ->green_X)
      return 1;
   Y += XYZ->green_Y;
   if (0x7fffffff - Y < XYZ->blue_X)
      return 1;
   Y += XYZ->blue_Y;

   if (Y != PNG_FP_1)
   {
      if (png_muldiv(&XYZ->red_X, XYZ->red_X, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->red_Y, XYZ->red_Y, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->red_Z, XYZ->red_Z, PNG_FP_1, Y) == 0)
         return 1;

      if (png_muldiv(&XYZ->green_X, XYZ->green_X, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->green_Y, XYZ->green_Y, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->green_Z, XYZ->green_Z, PNG_FP_1, Y) == 0)
         return 1;

      if (png_muldiv(&XYZ->blue_X, XYZ->blue_X, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->blue_Y, XYZ->blue_Y, PNG_FP_1, Y) == 0)
         return 1;
      if (png_muldiv(&XYZ->blue_Z, XYZ->blue_Z, PNG_FP_1, Y) == 0)
         return 1;
   }

   return 0;
}