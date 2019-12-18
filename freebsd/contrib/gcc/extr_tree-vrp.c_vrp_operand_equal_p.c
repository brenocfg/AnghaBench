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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int is_overflow_infinity (scalar_t__) ; 
 int /*<<< orphan*/  operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
vrp_operand_equal_p (tree val1, tree val2)
{
  if (val1 == val2)
    return true;
  if (!val1 || !val2 || !operand_equal_p (val1, val2, 0))
    return false;
  if (is_overflow_infinity (val1))
    return is_overflow_infinity (val2);
  return true;
}