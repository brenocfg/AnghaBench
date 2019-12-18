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
typedef  scalar_t__ TREE_NOTHROW ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_BUILT_IN ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ block_object_assign_decl ; 
 scalar_t__ build_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ builtin_function (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ lookup_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_list_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
build_block_object_assign_decl (void)
{
  tree func_type;
  if (block_object_assign_decl)
    return block_object_assign_decl;
  block_object_assign_decl = lookup_name (get_identifier ("_Block_object_assign"));
  if (block_object_assign_decl)
    return block_object_assign_decl;
  func_type =
	     build_function_type (void_type_node,
	       tree_cons (NULL_TREE, ptr_type_node,
			  tree_cons (NULL_TREE, ptr_type_node,
			             tree_cons (NULL_TREE, integer_type_node, void_list_node))));

  block_object_assign_decl = builtin_function ("_Block_object_assign", func_type,
					        0, NOT_BUILT_IN, 0, NULL_TREE);
  TREE_NOTHROW (block_object_assign_decl) = 0;
  return block_object_assign_decl;
}