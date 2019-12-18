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
typedef  int TREE_USED ;
typedef  int TREE_THIS_VOLATILE ;
typedef  int TREE_STATIC ;
typedef  int TREE_PUBLIC ;
typedef  int TREE_NOTHROW ;
typedef  int DECL_VISIBILITY_SPECIFIED ;
typedef  scalar_t__ DECL_VISIBILITY ;
typedef  int DECL_IGNORED_P ;
typedef  int DECL_EXTERNAL ;
typedef  int DECL_ARTIFICIAL ;

/* Variables and functions */
 int /*<<< orphan*/  FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ VISIBILITY_HIDDEN ; 
 scalar_t__ build_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_type_list (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ default_external_stack_protect_fail () ; 
 int /*<<< orphan*/  flag_pic ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 scalar_t__ stack_chk_fail_decl ; 
 int /*<<< orphan*/  void_type_node ; 

tree
default_hidden_stack_protect_fail (void)
{
#ifndef HAVE_GAS_HIDDEN
  return default_external_stack_protect_fail ();
#else
  tree t = stack_chk_fail_decl;

  if (!flag_pic)
    return default_external_stack_protect_fail ();

  if (t == NULL_TREE)
    {
      t = build_function_type_list (void_type_node, NULL_TREE);
      t = build_decl (FUNCTION_DECL,
		      get_identifier ("__stack_chk_fail_local"), t);
      TREE_STATIC (t) = 1;
      TREE_PUBLIC (t) = 1;
      DECL_EXTERNAL (t) = 1;
      TREE_USED (t) = 1;
      TREE_THIS_VOLATILE (t) = 1;
      TREE_NOTHROW (t) = 1;
      DECL_ARTIFICIAL (t) = 1;
      DECL_IGNORED_P (t) = 1;
      DECL_VISIBILITY_SPECIFIED (t) = 1;
      DECL_VISIBILITY (t) = VISIBILITY_HIDDEN;

      stack_chk_fail_decl = t;
    }

  return build_function_call_expr (t, NULL_TREE);
#endif
}