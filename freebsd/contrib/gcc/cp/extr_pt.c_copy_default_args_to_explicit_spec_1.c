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
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ hash_tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ void_list_node ; 

__attribute__((used)) static tree
copy_default_args_to_explicit_spec_1 (tree spec_types,
				      tree tmpl_types)
{
  tree new_spec_types;

  if (!spec_types)
    return NULL_TREE;

  if (spec_types == void_list_node)
    return void_list_node;

  /* Substitute into the rest of the list.  */
  new_spec_types =
    copy_default_args_to_explicit_spec_1 (TREE_CHAIN (spec_types),
					  TREE_CHAIN (tmpl_types));

  /* Add the default argument for this parameter.  */
  return hash_tree_cons (TREE_PURPOSE (tmpl_types),
			 TREE_VALUE (spec_types),
			 new_spec_types);
}