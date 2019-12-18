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
 int /*<<< orphan*/  lambda_vector_clear (int*,int) ; 

__attribute__((used)) static inline void
lambda_vector_mult_const (lambda_vector vec1, lambda_vector vec2,
			  int size, int const1)
{
  int i;

  if (const1 == 0)
    lambda_vector_clear (vec2, size);
  else
    for (i = 0; i < size; i++)
      vec2[i] = const1 * vec1[i];
}