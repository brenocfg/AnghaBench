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
typedef  int /*<<< orphan*/  double_int ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_INT_CST (int /*<<< orphan*/ ) ; 

double_int
tree_to_double_int (tree cst)
{
  /* We do not need to call double_int_restrict here to ensure the semantics as
     described, as this is the default one for trees.  */
  return TREE_INT_CST (cst);
}