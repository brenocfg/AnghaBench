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
typedef  int* png_const_bytep ;

/* Variables and functions */

__attribute__((used)) static int
check16(png_const_bytep bp, int b)
{
   int i = 16;

   do
      if (*bp != b) return 1;
   while (--i);

   return 0;
}