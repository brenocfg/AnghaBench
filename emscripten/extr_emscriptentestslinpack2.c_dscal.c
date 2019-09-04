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

void dscal ( int n, double sa, double x[], int incx )

/******************************************************************************/
/*
  Purpose:

    DSCAL scales a vector by a constant.

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

    Input, double SA, the multiplier.

    Input/output, double X[*], the vector to be scaled.

    Input, int INCX, the increment between successive entries of X.
*/
{
  int i;
  int ix;
  int m;

  if ( n <= 0 )
  {
  }
  else if ( incx == 1 )
  {
    m = n % 5;

    for ( i = 0; i < m; i++ )
    {
      x[i] = sa * x[i];
    }

    for ( i = m; i < n; i = i + 5 )
    {
      x[i]   = sa * x[i];
      x[i+1] = sa * x[i+1];
      x[i+2] = sa * x[i+2];
      x[i+3] = sa * x[i+3];
      x[i+4] = sa * x[i+4];
    }
  }
  else
  {
    if ( 0 <= incx )
    {
      ix = 0;
    }
    else
    {
      ix = ( - n + 1 ) * incx;
    }

    for ( i = 0; i < n; i++ )
    {
      x[ix] = sa * x[ix];
      ix = ix + incx;
    }
  }
  return;
}