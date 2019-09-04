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
 int /*<<< orphan*/  daxpy (int,double,double*,int,double*,int) ; 
 int /*<<< orphan*/  dscal (int,double,double*,int) ; 
 int idamax (int,double*,int) ; 

int dgefa ( double a[], int lda, int n, int ipvt[] )

/******************************************************************************/
/*
  Purpose:

    DGEFA factors a real general matrix.

  Modified:

    16 May 2005

  Author:

    C version by John Burkardt.

  Reference:

    Jack Dongarra, Cleve Moler, Jim Bunch and Pete Stewart,
    LINPACK User's Guide,
    SIAM, (Society for Industrial and Applied Mathematics),
    3600 University City Science Center,
    Philadelphia, PA, 19104-2688.
    ISBN 0-89871-172-X

  Parameters:

    Input/output, double A[LDA*N].
    On intput, the matrix to be factored.
    On output, an upper triangular matrix and the multipliers used to obtain
    it.  The factorization can be written A=L*U, where L is a product of
    permutation and unit lower triangular matrices, and U is upper triangular.

    Input, int LDA, the leading dimension of A.

    Input, int N, the order of the matrix A.

    Output, int IPVT[N], the pivot indices.

    Output, int DGEFA, singularity indicator.
    0, normal value.
    K, if U(K,K) == 0.  This is not an error condition for this subroutine,
    but it does indicate that DGESL or DGEDI will divide by zero if called.
    Use RCOND in DGECO for a reliable indication of singularity.
*/
{
  int info;
  int j;
  int k;
  int l;
  double t;
/*
  Gaussian elimination with partial pivoting.
*/
  info = 0;

  for ( k = 1; k <= n-1; k++ )
  {
/*
  Find L = pivot index.
*/
    l = idamax ( n-k+1, a+(k-1)+(k-1)*lda, 1 ) + k - 1;
    ipvt[k-1] = l;
/*
  Zero pivot implies this column already triangularized.
*/
    if ( a[l-1+(k-1)*lda] == 0.0 )
    {
      info = k;
      continue;
    }
/*
  Interchange if necessary.
*/
    if ( l != k )
    {
      t = a[l-1+(k-1)*lda];
      a[l-1+(k-1)*lda] = a[k-1+(k-1)*lda];
      a[k-1+(k-1)*lda] = t;
    }
/*
  Compute multipliers.
*/
    t = -1.0 / a[k-1+(k-1)*lda];

    dscal ( n-k, t, a+k+(k-1)*lda, 1 );
/*
  Row elimination with column indexing.
*/
    for ( j = k+1; j <= n; j++ )
    {
      t = a[l-1+(j-1)*lda];
      if ( l != k )
      {
        a[l-1+(j-1)*lda] = a[k-1+(j-1)*lda];
        a[k-1+(j-1)*lda] = t;
      }
      daxpy ( n-k, t, a+k+(k-1)*lda, 1, a+k+(j-1)*lda, 1 );
    }

  }

  ipvt[n-1] = n;

  if ( a[n-1+(n-1)*lda] == 0.0 )
  {
    info = n;
  }

  return info;
}