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
typedef  scalar_t__* lambda_vector ;

/* Variables and functions */

__attribute__((used)) static inline bool
lambda_vector_lexico_pos (lambda_vector v, 
			  unsigned n)
{
  unsigned i;
  for (i = 0; i < n; i++)
    {
      if (v[i] == 0)
	continue;
      if (v[i] < 0)
	return false;
      if (v[i] > 0)
	return true;
    }
  return true;
}