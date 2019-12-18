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
 scalar_t__ TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
int_cst_hash_eq (const void *x, const void *y)
{
  tree xt = (tree) x;
  tree yt = (tree) y;

  return (TREE_TYPE (xt) == TREE_TYPE (yt)
	  && TREE_INT_CST_HIGH (xt) == TREE_INT_CST_HIGH (yt)
	  && TREE_INT_CST_LOW (xt) == TREE_INT_CST_LOW (yt));
}