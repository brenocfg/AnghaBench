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
png_row_in_interlace_pass(png_uint_32 y, int pass)
{
   /* Is row 'y' in pass 'pass'? */
   int x;
   y &= 7;
   ++pass;
   for (x=0; x<8; ++x) if (adam7[y][x] == pass)
      return 1;

   return 0;
}