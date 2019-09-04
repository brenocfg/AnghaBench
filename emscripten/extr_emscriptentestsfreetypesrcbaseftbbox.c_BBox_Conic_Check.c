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
typedef  int FT_Pos ;

/* Variables and functions */
 int FT_MulDiv (int,int,int) ; 

__attribute__((used)) static void
  BBox_Conic_Check( FT_Pos   y1,
                    FT_Pos   y2,
                    FT_Pos   y3,
                    FT_Pos*  min,
                    FT_Pos*  max )
  {
    if ( y1 <= y3 && y2 == y1 )     /* flat arc */
      goto Suite;

    if ( y1 < y3 )
    {
      if ( y2 >= y1 && y2 <= y3 )   /* ascending arc */
        goto Suite;
    }
    else
    {
      if ( y2 >= y3 && y2 <= y1 )   /* descending arc */
      {
        y2 = y1;
        y1 = y3;
        y3 = y2;
        goto Suite;
      }
    }

    y1 = y3 = y1 - FT_MulDiv( y2 - y1, y2 - y1, y1 - 2*y2 + y3 );

  Suite:
    if ( y1 < *min ) *min = y1;
    if ( y3 > *max ) *max = y3;
  }