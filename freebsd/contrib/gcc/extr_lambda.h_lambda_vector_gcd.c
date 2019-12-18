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
typedef  int* lambda_vector ;

/* Variables and functions */
 int gcd (int,int) ; 

__attribute__((used)) static inline int
lambda_vector_gcd (lambda_vector vector, int size)
{
  int i;
  int gcd1 = 0;

  if (size > 0)
    {
      gcd1 = vector[0];
      for (i = 1; i < size; i++)
	gcd1 = gcd (gcd1, vector[i]);
    }
  return gcd1;
}