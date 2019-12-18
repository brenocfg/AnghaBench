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
 scalar_t__ COMPARISON_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
fp_predicate (tree expr)
{
  return (COMPARISON_CLASS_P (expr)
	  && FLOAT_TYPE_P (TREE_TYPE (TREE_OPERAND (expr, 0))));
}