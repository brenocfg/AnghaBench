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
typedef  float* vec2_t ;

/* Variables and functions */
 int qfalse ; 
 int qtrue ; 

int Intersection(vec2_t p1, vec2_t p2, vec2_t p3, vec2_t p4, vec2_t out)
{
   float x1, dx1, dy1, x2, dx2, dy2, d;

   dx1 = p2[0] - p1[0];
   dy1 = p2[1] - p1[1];
   dx2 = p4[0] - p3[0];
   dy2 = p4[1] - p3[1];

   d = dy1 * dx2 - dx1 * dy2;
   if (d != 0)
   {
      x1 = p1[1] * dx1 - p1[0] * dy1;
      x2 = p3[1] * dx2 - p3[0] * dy2;
      out[0] = (int) ((dx1 * x2 - dx2 * x1) / d);
      out[1] = (int) ((dy1 * x2 - dy2 * x1) / d);
		return qtrue;
   } //end if
   else
   {
      return qfalse;
   } //end else
}