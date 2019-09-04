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
 scalar_t__ malloc (int) ; 
 double r8_random (int*) ; 

double *r8mat_gen ( int lda, int n )

/******************************************************************************/
/*
  Purpose:

    R8MAT_GEN generates a random R8MAT.

  Modified:

    06 June 2005

  Parameters:

    Input, integer LDA, the leading dimension of the matrix.

    Input, integer N, the order of the matrix.

    Output, double R8MAT_GEN[LDA*N], the N by N matrix.
*/
{
  double *a;
  int i;
  int init[4] = { 1, 2, 3, 1325 };
  int j;

  a = ( double * ) malloc ( lda * n * sizeof ( double ) );

  for ( j = 1; j <= n; j++ )
  {
    for ( i = 1; i <= n; i++ )
    {
      a[i-1+(j-1)*lda] = r8_random ( init ) - 0.5;
    }
  }

  return a;
}