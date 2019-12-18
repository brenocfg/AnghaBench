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

__attribute__((used)) static png_uint_32
png_pass_rows(png_uint_32 height, int pass)
{
   png_uint_32 tiles = height>>3;
   png_uint_32 rows = 0;
   unsigned int x, y;

   height &= 7;
   ++pass;
   for (y=0; y<8; ++y) for (x=0; x<8; ++x) if (adam7[y][x] == pass)
   {
      rows += tiles;
      if (y < height) ++rows;
      break; /* i.e. break the 'x', column, loop. */
   }

   return rows;
}