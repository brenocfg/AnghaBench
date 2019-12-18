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
 int** adam7 ; 

__attribute__((used)) static int
png_col_in_interlace_pass(png_uint_32 x, int pass)
{
   /* Is column 'x' in pass 'pass'? */
   int y;
   x &= 7;
   ++pass;
   for (y=0; y<8; ++y) if (adam7[y][x] == pass)
      return 1;

   return 0;
}