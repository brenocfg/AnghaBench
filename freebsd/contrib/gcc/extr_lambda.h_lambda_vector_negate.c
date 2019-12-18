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
typedef  int /*<<< orphan*/  lambda_vector ;

/* Variables and functions */
 int /*<<< orphan*/  lambda_vector_mult_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void 
lambda_vector_negate (lambda_vector vec1, lambda_vector vec2,
		      int size)
{
  lambda_vector_mult_const (vec1, vec2, size, -1);
}