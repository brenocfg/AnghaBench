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
typedef  int FT_Fixed ;

/* Variables and functions */
 int FT_MulFix (int,int) ; 
 int /*<<< orphan*/  FT_UNUSED (int) ; 

__attribute__((used)) static void
  test_cubic_extrema( FT_Pos    y1,
                      FT_Pos    y2,
                      FT_Pos    y3,
                      FT_Pos    y4,
                      FT_Fixed  u,
                      FT_Pos*   min,
                      FT_Pos*   max )
  {
 /* FT_Pos    a = y4 - 3*y3 + 3*y2 - y1; */
    FT_Pos    b = y3 - 2*y2 + y1;
    FT_Pos    c = y2 - y1;
    FT_Pos    d = y1;
    FT_Pos    y;
    FT_Fixed  uu;

    FT_UNUSED ( y4 );


    /* The polynomial is                      */
    /*                                        */
    /*    P(x) = a*x^3 + 3b*x^2 + 3c*x + d  , */
    /*                                        */
    /*   dP/dx = 3a*x^2 + 6b*x + 3c         . */
    /*                                        */
    /* However, we also have                  */
    /*                                        */
    /*   dP/dx(u) = 0                       , */
    /*                                        */
    /* which implies by subtraction that      */
    /*                                        */
    /*   P(u) = b*u^2 + 2c*u + d            . */

    if ( u > 0 && u < 0x10000L )
    {
      uu = FT_MulFix( u, u );
      y  = d + FT_MulFix( c, 2*u ) + FT_MulFix( b, uu );

      if ( y < *min ) *min = y;
      if ( y > *max ) *max = y;
    }
  }