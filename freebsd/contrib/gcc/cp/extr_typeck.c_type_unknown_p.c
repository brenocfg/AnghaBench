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
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ unknown_type_node ; 

int
type_unknown_p (tree exp)
{
  return (TREE_CODE (exp) == TREE_LIST
	  || TREE_TYPE (exp) == unknown_type_node);
}