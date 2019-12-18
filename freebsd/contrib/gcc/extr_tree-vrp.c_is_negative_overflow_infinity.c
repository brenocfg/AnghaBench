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
 scalar_t__ CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_overflow_infinity (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
is_negative_overflow_infinity (tree val)
{
  return (needs_overflow_infinity (TREE_TYPE (val))
	  && CONSTANT_CLASS_P (val)
	  && TREE_OVERFLOW (val)
	  && operand_equal_p (val, TYPE_MIN_VALUE (TREE_TYPE (val)), 0));
}