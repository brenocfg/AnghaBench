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
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_type_quals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

tree
build_ptrmemfunc_access_expr (tree ptrmem, tree member_name)
{
  tree ptrmem_type;
  tree member;
  tree member_type;

  /* This code is a stripped down version of
     build_class_member_access_expr.  It does not work to use that
     routine directly because it expects the object to be of class
     type.  */
  ptrmem_type = TREE_TYPE (ptrmem);
  gcc_assert (TYPE_PTRMEMFUNC_P (ptrmem_type));
  member = lookup_member (ptrmem_type, member_name, /*protect=*/0,
			  /*want_type=*/false);
  member_type = cp_build_qualified_type (TREE_TYPE (member),
					 cp_type_quals (ptrmem_type));
  return fold_build3 (COMPONENT_REF, member_type,
		      ptrmem, member, NULL_TREE);
}