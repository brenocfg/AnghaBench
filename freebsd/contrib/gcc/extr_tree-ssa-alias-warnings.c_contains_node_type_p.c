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
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  contains_node_type_p_callback ; 
 scalar_t__ walk_tree_without_duplicates (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool
contains_node_type_p (tree t, int type)
{
  return (walk_tree_without_duplicates (&t, contains_node_type_p_callback,
					(void *) &type)
	  != NULL_TREE);
}