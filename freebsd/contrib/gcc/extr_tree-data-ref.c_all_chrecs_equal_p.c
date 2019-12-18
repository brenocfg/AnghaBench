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
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,int) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eq_evolutions_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool 
all_chrecs_equal_p (tree chrec)
{
  int j;

  for (j = 0; j < TREE_VEC_LENGTH (chrec) - 1; j++)
    if (!eq_evolutions_p (TREE_VEC_ELT (chrec, j),
			  TREE_VEC_ELT (chrec, j + 1)))
      return false;

  return true;
}