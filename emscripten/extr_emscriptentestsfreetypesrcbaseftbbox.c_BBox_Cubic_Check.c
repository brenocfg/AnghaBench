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
typedef  int FT_ULong ;
typedef  scalar_t__ FT_Pos ;
typedef  int /*<<< orphan*/  FT_Int32 ;
typedef  int FT_Fixed ;

/* Variables and functions */
 int FT_DivFix (scalar_t__,scalar_t__) ; 
 scalar_t__ FT_MulFix (scalar_t__,scalar_t__) ; 
 scalar_t__ FT_SqrtFixed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_cubic_extrema (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void
  BBox_Cubic_Check( FT_Pos   y1,
                    FT_Pos   y2,
                    FT_Pos   y3,
                    FT_Pos   y4,
                    FT_Pos*  min,
                    FT_Pos*  max )
  {
    /* always compare first and last points */
    if      ( y1 < *min )  *min = y1;
    else if ( y1 > *max )  *max = y1;

    if      ( y4 < *min )  *min = y4;
    else if ( y4 > *max )  *max = y4;

    /* now, try to see if there are split points here */
    if ( y1 <= y4 )
    {
      /* flat or ascending arc test */
      if ( y1 <= y2 && y2 <= y4 && y1 <= y3 && y3 <= y4 )
        return;
    }
    else /* y1 > y4 */
    {
      /* descending arc test */
      if ( y1 >= y2 && y2 >= y4 && y1 >= y3 && y3 >= y4 )
        return;
    }

    /* There are some split points.  Find them. */
    {
      FT_Pos    a = y4 - 3*y3 + 3*y2 - y1;
      FT_Pos    b = y3 - 2*y2 + y1;
      FT_Pos    c = y2 - y1;
      FT_Pos    d;
      FT_Fixed  t;


      /* We need to solve `ax^2+2bx+c' here, without floating points!      */
      /* The trick is to normalize to a different representation in order  */
      /* to use our 16.16 fixed point routines.                            */
      /*                                                                   */
      /* We compute FT_MulFix(b,b) and FT_MulFix(a,c) after normalization. */
      /* These values must fit into a single 16.16 value.                  */
      /*                                                                   */
      /* We normalize a, b, and c to `8.16' fixed float values to ensure   */
      /* that its product is held in a `16.16' value.                      */

      {
        FT_ULong  t1, t2;
        int       shift = 0;


        /* The following computation is based on the fact that for   */
        /* any value `y', if `n' is the position of the most         */
        /* significant bit of `abs(y)' (starting from 0 for the      */
        /* least significant bit), then `y' is in the range          */
        /*                                                           */
        /*   -2^n..2^n-1                                             */
        /*                                                           */
        /* We want to shift `a', `b', and `c' concurrently in order  */
        /* to ensure that they all fit in 8.16 values, which maps    */
        /* to the integer range `-2^23..2^23-1'.                     */
        /*                                                           */
        /* Necessarily, we need to shift `a', `b', and `c' so that   */
        /* the most significant bit of its absolute values is at     */
        /* _most_ at position 23.                                    */
        /*                                                           */
        /* We begin by computing `t1' as the bitwise `OR' of the     */
        /* absolute values of `a', `b', `c'.                         */

        t1  = (FT_ULong)( ( a >= 0 ) ? a : -a );
        t2  = (FT_ULong)( ( b >= 0 ) ? b : -b );
        t1 |= t2;
        t2  = (FT_ULong)( ( c >= 0 ) ? c : -c );
        t1 |= t2;

        /* Now we can be sure that the most significant bit of `t1'  */
        /* is the most significant bit of either `a', `b', or `c',   */
        /* depending on the greatest integer range of the particular */
        /* variable.                                                 */
        /*                                                           */
        /* Next, we compute the `shift', by shifting `t1' as many    */
        /* times as necessary to move its MSB to position 23.  This  */
        /* corresponds to a value of `t1' that is in the range       */
        /* 0x40_0000..0x7F_FFFF.                                     */
        /*                                                           */
        /* Finally, we shift `a', `b', and `c' by the same amount.   */
        /* This ensures that all values are now in the range         */
        /* -2^23..2^23, i.e., they are now expressed as 8.16         */
        /* fixed-float numbers.  This also means that we are using   */
        /* 24 bits of precision to compute the zeros, independently  */
        /* of the range of the original polynomial coefficients.     */
        /*                                                           */
        /* This algorithm should ensure reasonably accurate values   */
        /* for the zeros.  Note that they are only expressed with    */
        /* 16 bits when computing the extrema (the zeros need to     */
        /* be in 0..1 exclusive to be considered part of the arc).   */

        if ( t1 == 0 )  /* all coefficients are 0! */
          return;

        if ( t1 > 0x7FFFFFUL )
        {
          do
          {
            shift++;
            t1 >>= 1;

          } while ( t1 > 0x7FFFFFUL );

          /* this loses some bits of precision, but we use 24 of them */
          /* for the computation anyway                               */
          a >>= shift;
          b >>= shift;
          c >>= shift;
        }
        else if ( t1 < 0x400000UL )
        {
          do
          {
            shift++;
            t1 <<= 1;

          } while ( t1 < 0x400000UL );

          a <<= shift;
          b <<= shift;
          c <<= shift;
        }
      }

      /* handle a == 0 */
      if ( a == 0 )
      {
        if ( b != 0 )
        {
          t = - FT_DivFix( c, b ) / 2;
          test_cubic_extrema( y1, y2, y3, y4, t, min, max );
        }
      }
      else
      {
        /* solve the equation now */
        d = FT_MulFix( b, b ) - FT_MulFix( a, c );
        if ( d < 0 )
          return;

        if ( d == 0 )
        {
          /* there is a single split point at -b/a */
          t = - FT_DivFix( b, a );
          test_cubic_extrema( y1, y2, y3, y4, t, min, max );
        }
        else
        {
          /* there are two solutions; we need to filter them */
          d = FT_SqrtFixed( (FT_Int32)d );
          t = - FT_DivFix( b - d, a );
          test_cubic_extrema( y1, y2, y3, y4, t, min, max );

          t = - FT_DivFix( b + d, a );
          test_cubic_extrema( y1, y2, y3, y4, t, min, max );
        }
      }
    }
  }