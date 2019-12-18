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
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_method_type_directly (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_offset_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_ptrmemfunc_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_type_quals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
build_ptrmem_type (tree class_type, tree member_type)
{
  if (TREE_CODE (member_type) == METHOD_TYPE)
    {
      tree arg_types;

      arg_types = TYPE_ARG_TYPES (member_type);
      class_type = (cp_build_qualified_type
		    (class_type,
		     cp_type_quals (TREE_TYPE (TREE_VALUE (arg_types)))));
      member_type
	= build_method_type_directly (class_type,
				      TREE_TYPE (member_type),
				      TREE_CHAIN (arg_types));
      return build_ptrmemfunc_type (build_pointer_type (member_type));
    }
  else
    {
      gcc_assert (TREE_CODE (member_type) != FUNCTION_TYPE);
      return build_offset_type (class_type, member_type);
    }
}