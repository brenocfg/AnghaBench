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
 int /*<<< orphan*/  BINFO_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  COND_EXPR ; 
 int LOOKUP_NONVIRTUAL ; 
 int LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TYPE_HAS_TRIVIAL_DESTRUCTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_dtor_identifier ; 
 scalar_t__ build_special_member_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  c_common_truthvalue_conversion (scalar_t__) ; 
 int /*<<< orphan*/  current_class_ref ; 
 int /*<<< orphan*/  finish_eh_cleanup (scalar_t__) ; 
 scalar_t__ fold_build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
expand_cleanup_for_base (tree binfo, tree flag)
{
  tree expr;

  if (TYPE_HAS_TRIVIAL_DESTRUCTOR (BINFO_TYPE (binfo)))
    return;

  /* Call the destructor.  */
  expr = build_special_member_call (current_class_ref,
				    base_dtor_identifier,
				    NULL_TREE,
				    binfo,
				    LOOKUP_NORMAL | LOOKUP_NONVIRTUAL);
  if (flag)
    expr = fold_build3 (COND_EXPR, void_type_node,
			c_common_truthvalue_conversion (flag),
			expr, integer_zero_node);

  finish_eh_cleanup (expr);
}