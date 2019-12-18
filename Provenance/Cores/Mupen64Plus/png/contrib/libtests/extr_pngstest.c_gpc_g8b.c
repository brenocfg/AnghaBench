#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t ig; int dg; } ;
struct TYPE_6__ {int a; size_t r; size_t g; size_t b; } ;
typedef  TYPE_1__ Pixel ;
typedef  TYPE_2__ Background ;

/* Variables and functions */
 double YfromRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sRGB (double) ; 
 int /*<<< orphan*/ * sRGB_to_d ; 

__attribute__((used)) static void
gpc_g8b(Pixel *out, const Pixel *in, const Background *back)
{
   if (in->a <= 0)
      out->r = out->g = out->b = back->ig;

   else if (in->a >= 255)
   {
      if (in->r == in->g && in->g == in->b)
         out->r = out->g = out->b = in->g;

      else
         out->r = out->g = out->b = sRGB(YfromRGB(
            sRGB_to_d[in->r], sRGB_to_d[in->g], sRGB_to_d[in->b]));
   }

   else
   {
      double a = in->a/255.;

      out->r = out->g = out->b = sRGB(a * YfromRGB(sRGB_to_d[in->r],
         sRGB_to_d[in->g], sRGB_to_d[in->b]) + back->dg * (1-a));
   }

   out->a = 255;
}