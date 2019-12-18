#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct arg {TYPE_1__* color; } ;
typedef  scalar_t__* png_uint_16p ;
typedef  scalar_t__ png_uint_16 ;
struct TYPE_2__ {double const red; double const green; double const blue; } ;

/* Variables and functions */
 int alpha_calc (struct arg*,double,double) ; 
 scalar_t__ round (double) ; 

__attribute__((used)) static void
pixel(png_uint_16p p, struct arg *args, int nargs, double x, double y)
{
   /* Fill in the pixel by checking each shape (args[nargs]) for effects on
    * the corresponding sample:
    */
   double r=0, g=0, b=0, a=0;

   while (--nargs >= 0 && a != 1)
   {
      /* NOTE: alpha_calc can return a value outside the range 0..1 with the
       * bicubic filter.
       */
      const double alpha = alpha_calc(args+nargs, x, y) * (1-a);

      r += alpha * args[nargs].color->red;
      g += alpha * args[nargs].color->green;
      b += alpha * args[nargs].color->blue;
      a += alpha;
   }

   /* 'a' may be negative or greater than 1; if it is, negative clamp the
    * pixel to 0 if >1 clamp r/g/b:
    */
   if (a > 0)
   {
      if (a > 1)
      {
         if (r > 1) r = 1;
         if (g > 1) g = 1;
         if (b > 1) b = 1;
         a = 1;
      }

      /* And fill in the pixel: */
      p[0] = (png_uint_16)/*SAFE*/round(r * 65535);
      p[1] = (png_uint_16)/*SAFE*/round(g * 65535);
      p[2] = (png_uint_16)/*SAFE*/round(b * 65535);
      p[3] = (png_uint_16)/*SAFE*/round(a * 65535);
   }

   else
      p[3] = p[2] = p[1] = p[0] = 0;
}