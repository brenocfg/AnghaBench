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
 int** adam7 ; 

__attribute__((used)) static int
png_pass_col_shift(int pass)
{
   int x, y, base=(-1), inc=8;
   ++pass;
   for (x=0; x<8; ++x) for (y=0; y<8; ++y) if (adam7[y][x] == pass)
   {
      if (base == (-1))
         base = x;
      else if (base == x)
         {}
      else if (inc == x-base)
         base=x;
      else if (inc == 8)
         inc = x-base, base=x;
      else if (inc != x-base)
         return 0xff; /* error - more than one 'inc' value! */
   }

   if (base == (-1)) return 0xfe; /* error - no row in pass! */

   /* The shift is always 1, 2 or 3 - no pass has all the rows! */
   switch (inc)
   {
case 1: return 0; /* pass 7 has all the columns */
case 2: return 1;
case 4: return 2;
case 8: return 3;
default: break;
   }

   /* error - unrecognized 'inc' */
   return (inc << 8) + 0xfd;
}