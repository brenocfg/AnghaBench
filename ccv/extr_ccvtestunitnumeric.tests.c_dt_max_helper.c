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
 float square (int) ; 

void dt_max_helper(float *src, float *dst, int *ptr, int step, 
	       int s1, int s2, int d1, int d2, float a, float b) {
 if (d2 >= d1) {
   int d = (d1+d2) >> 1;
   int s = s1;
   int p;
   for (p = s1+1; p <= s2; p++)
     if (src[s*step] - a*square(d-s) - b*(d-s) <
	 src[p*step] - a*square(d-p) - b*(d-p))
	s = p;
   dst[d*step] = src[s*step] - a*square(d-s) - b*(d-s);
   ptr[d*step] = s;
   dt_max_helper(src, dst, ptr, step, s1, s, d1, d-1, a, b);
   dt_max_helper(src, dst, ptr, step, s, s2, d+1, d2, a, b);
 }
}