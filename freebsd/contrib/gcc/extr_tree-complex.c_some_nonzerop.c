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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ REAL_CST ; 
 int REAL_VALUES_IDENTICAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst0 ; 
 int integer_zerop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
some_nonzerop (tree t)
{
  int zerop = false;

  if (TREE_CODE (t) == REAL_CST)
    zerop = REAL_VALUES_IDENTICAL (TREE_REAL_CST (t), dconst0);
  else if (TREE_CODE (t) == INTEGER_CST)
    zerop = integer_zerop (t);

  return !zerop;
}