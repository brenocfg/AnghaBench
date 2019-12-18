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
typedef  int png_uint_32 ;

/* Variables and functions */

__attribute__((used)) static png_uint_32
png_row_from_pass_row(png_uint_32 yIn, int pass)
{
   /* By examination of the array: */
   switch (pass)
   {
case 0: return yIn * 8;
case 1: return yIn * 8;
case 2: return yIn * 8 + 4;
case 3: return yIn * 4;
case 4: return yIn * 4 + 2;
case 5: return yIn * 2;
case 6: return yIn * 2 + 1;
default: break;
   }

   return 0xff; /* bad pass number */
}