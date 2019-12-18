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
 int BUCKET_A_SIZE ; 
 int BUCKET_B_SIZE ; 
 int /*<<< orphan*/  construct_SA (unsigned char const*,int*,int*,int*,int,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int sort_typeBstar (unsigned char const*,int*,int*,int*,int,int) ; 

int
divsufsort(const unsigned char *T, int *SA, int n, int openMP) {
  int *bucket_A, *bucket_B;
  int m;
  int err = 0;

  /* Check arguments. */
  if((T == NULL) || (SA == NULL) || (n < 0)) { return -1; }
  else if(n == 0) { return 0; }
  else if(n == 1) { SA[0] = 0; return 0; }
  else if(n == 2) { m = (T[0] < T[1]); SA[m ^ 1] = 0, SA[m] = 1; return 0; }

  bucket_A = (int *)malloc(BUCKET_A_SIZE * sizeof(int));
  bucket_B = (int *)malloc(BUCKET_B_SIZE * sizeof(int));

  /* Suffixsort. */
  if((bucket_A != NULL) && (bucket_B != NULL)) {
    m = sort_typeBstar(T, SA, bucket_A, bucket_B, n, openMP);
    construct_SA(T, SA, bucket_A, bucket_B, n, m);
  } else {
    err = -2;
  }

  free(bucket_B);
  free(bucket_A);

  return err;
}