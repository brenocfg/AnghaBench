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
typedef  int CF2_Int ;
typedef  int CF2_Fixed ;

/* Variables and functions */
 int SUB_INT32 (int,int) ; 

__attribute__((used)) static CF2_Int
  cf2_getWindingMomentum( CF2_Fixed  x1,
                          CF2_Fixed  y1,
                          CF2_Fixed  x2,
                          CF2_Fixed  y2 )
  {
    /* cross product of pt1 position from origin with pt2 position from  */
    /* pt1; we reduce the precision so that the result fits into 32 bits */

    return ( x1 >> 16 ) * ( SUB_INT32( y2, y1 ) >> 16 ) -
           ( y1 >> 16 ) * ( SUB_INT32( x2, x1 ) >> 16 );
  }