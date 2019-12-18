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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ evolution_function_is_affine_p (int /*<<< orphan*/ ) ; 
 scalar_t__ evolution_function_is_constant_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool 
evolution_function_is_affine_or_constant_p (tree chrec)
{
  return evolution_function_is_affine_p (chrec) 
    || evolution_function_is_constant_p (chrec);
}