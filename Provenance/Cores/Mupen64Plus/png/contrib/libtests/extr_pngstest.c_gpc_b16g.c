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
struct TYPE_7__ {double ig; double dg; } ;
struct TYPE_6__ {int a; double r; double g; double b; } ;
typedef  TYPE_1__ Pixel ;
typedef  TYPE_2__ Background ;

/* Variables and functions */
 double sRGB (double) ; 

__attribute__((used)) static void
gpc_b16g(Pixel *out, const Pixel *in, const Background *back)
{
   if (in->a <= 0)
      out->r = out->g = out->b = back->ig;

   else
   {
      double a = in->a/65535.;
      double a1 = 1-a;

      a /= 65535;
      out->r = out->g = out->b = sRGB(in->g * a + back->dg * a1);
   }

   out->a = 255;
}