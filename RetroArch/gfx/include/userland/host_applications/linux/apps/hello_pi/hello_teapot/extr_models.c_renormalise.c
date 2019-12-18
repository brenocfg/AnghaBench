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

/* Variables and functions */
 float sqrtf (float) ; 

__attribute__((used)) static void renormalise(float *verts, int numvertices)
{
   int i;
   float *v = verts;
   for (i=0;i<numvertices; i++) {
      float x = v[0];
      float y = v[1];
      float z = v[2];
      float scale = 1.0f/sqrtf(x*x + y*y + z*z);
      *v++ = x * scale;
      *v++ = y * scale;
      *v++ = z * scale;
   }
}