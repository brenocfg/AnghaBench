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
 float vcos_max (float,float) ; 
 float vcos_min (float,float) ; 

__attribute__((used)) static void centre_and_rescale(float *verts, int numvertices)
{
   float cx=0.0f, cy=0.0f, cz=0.0f, scale=0.0f;
   float minx=0.0f, miny=0.0f, minz=0.0f;
   float maxx=0.0f, maxy=0.0f, maxz=0.0f;
   int i;
   float *v = verts;
   minx = maxx = verts[0];
   miny = maxy = verts[1];
   minz = maxz = verts[2];
   for (i=0; i<numvertices; i++) {
      float x = *v++;
      float y = *v++;
      float z = *v++;
      minx = vcos_min(minx, x);
      miny = vcos_min(miny, y);
      minz = vcos_min(minz, z);
      maxx = vcos_max(maxx, x);
      maxy = vcos_max(maxy, y);
      maxz = vcos_max(maxz, z);
      cx += x;
      cy += y;
      cz += z;
   }
   cx /= (float)numvertices;
   cy /= (float)numvertices;
   cz /= (float)numvertices;
   scale = 3.0f / (maxx-minx + maxy-miny + maxz-minz);
   v = verts;
   for (i=0; i<numvertices; i++) {
      *v = (*v-cx) * scale; v++;
      *v = (*v-cy) * scale; v++;
      *v = (*v-cz) * scale; v++;
   }
}