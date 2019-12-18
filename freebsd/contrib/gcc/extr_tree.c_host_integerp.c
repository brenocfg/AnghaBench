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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_IS_SIZETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 

int
host_integerp (tree t, int pos)
{
  return (TREE_CODE (t) == INTEGER_CST
	  && ((TREE_INT_CST_HIGH (t) == 0
	       && (HOST_WIDE_INT) TREE_INT_CST_LOW (t) >= 0)
	      || (! pos && TREE_INT_CST_HIGH (t) == -1
		  && (HOST_WIDE_INT) TREE_INT_CST_LOW (t) < 0
		  && (!TYPE_UNSIGNED (TREE_TYPE (t))
		      || TYPE_IS_SIZETYPE (TREE_TYPE (t))))
	      || (pos && TREE_INT_CST_HIGH (t) == 0)));
}