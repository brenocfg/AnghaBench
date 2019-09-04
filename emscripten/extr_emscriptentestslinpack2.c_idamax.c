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
 double r8_abs (double) ; 

int idamax ( int n, double dx[], int incx )

/******************************************************************************/
/*
  Purpose:

    IDAMAX finds the index of the vector element of maximum absolute value.

  Discussion:

    WARNING: This index is a 1-based index, not a 0-based index!

  Modified:

    30 March 2007

  Author:

    FORTRAN77 original by Jack Dongarra, Cleve Moler, Jim Bunch, Pete Stewart.
    C version by John Burkardt

  Reference:

    Jack Dongarra, Cleve Moler, Jim Bunch, Pete Stewart,
    LINPACK User's Guide,
    SIAM, 1979.

    Charles Lawson, Richard Hanson, David Kincaid, Fred Krogh,
    Basic Linear Algebra Subprograms for Fortran Usage,
    Algorithm 539,
    ACM Transactions on Mathematical Software,
    Volume 5, Number 3, September 1979, pages 308-323.

  Parameters:

    Input, int N, the number of entries in the vector.

    Input, double X[*], the vector to be examined.

    Input, int INCX, the increment between successive entries of SX.

    Output, int IDAMAX, the index of the element of maximum
    absolute value.
*/
{
  double dmax;
  int i;
  int ix;
  int value;

  value = 0;

  if ( n < 1 || incx <= 0 )
  {
    return value;
  }

  value = 1;

  if ( n == 1 )
  {
    return value;
  }

  if ( incx == 1 )
  {
    dmax = r8_abs ( dx[0] );

    for ( i = 1; i < n; i++ )
    {
      if ( dmax < r8_abs ( dx[i] ) )
      {
        value = i + 1;
        dmax = r8_abs ( dx[i] );
      }
    }
  }
  else
  {
    ix = 0;
    dmax = r8_abs ( dx[0] );
    ix = ix + incx;

    for ( i = 1; i < n; i++ )
    {
      if ( dmax < r8_abs ( dx[ix] ) )
      {
        value = i + 1;
        dmax = r8_abs ( dx[ix] );
      }
      ix = ix + incx;
    }
  }

  return value;
}