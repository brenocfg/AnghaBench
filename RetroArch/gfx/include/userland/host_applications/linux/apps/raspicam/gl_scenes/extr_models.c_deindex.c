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
typedef  int GLsizei ;

/* Variables and functions */

__attribute__((used)) static void deindex(float *dst, const float *src, const unsigned short *indexes, GLsizei size, GLsizei count)
{
   int i;
   for (i=0; i<count; i++) {
      int ind = size * (indexes[0]-1);
      *dst++ = src[ind + 0];
      *dst++ = src[ind + 1];
      // todo: optimise - move out of loop
      if (size >= 3) *dst++ = src[ind + 2];
      indexes += 3;
   }
}