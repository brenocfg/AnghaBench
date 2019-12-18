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
struct cgraph_node {int dummy; } ;
struct cgraph_edge {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ CALL_EXPR ; 
 scalar_t__ CONST_DECL ; 
 int /*<<< orphan*/  CONST_IPATYPE ; 
 int /*<<< orphan*/  CONST_IPATYPE_REF ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 int /*<<< orphan*/  FORMAL_IPATYPE ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  UNKNOWN_IPATYPE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_call_expr_in (int /*<<< orphan*/ ) ; 
 struct cgraph_node* ipa_callsite_caller (struct cgraph_edge*) ; 
 scalar_t__ ipa_callsite_param_count (struct cgraph_edge*) ; 
 int /*<<< orphan*/  ipa_callsite_param_map_create (struct cgraph_edge*) ; 
 int /*<<< orphan*/  ipa_callsite_param_set_info_type (struct cgraph_edge*,int,scalar_t__) ; 
 int /*<<< orphan*/  ipa_callsite_param_set_info_type_formal (struct cgraph_edge*,int,int) ; 
 int /*<<< orphan*/  ipa_callsite_param_set_type (struct cgraph_edge*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_callsite_tree (struct cgraph_edge*) ; 
 scalar_t__ ipa_method_is_modified (struct cgraph_node*,int) ; 
 int ipa_method_tree_map (struct cgraph_node*,scalar_t__) ; 

void
ipa_callsite_compute_param (struct cgraph_edge *cs)
{
  tree call_tree;
  tree arg, cst_decl;
  int arg_num;
  int i;
  struct cgraph_node *mt;

  if (ipa_callsite_param_count (cs) == 0)
    return;
  ipa_callsite_param_map_create (cs);
  call_tree = get_call_expr_in (ipa_callsite_tree (cs));
  gcc_assert (TREE_CODE (call_tree) == CALL_EXPR);
  arg = TREE_OPERAND (call_tree, 1);
  arg_num = 0;

  for (; arg != NULL_TREE; arg = TREE_CHAIN (arg))
    {
      /* If the formal parameter was passed as argument, we store 
         FORMAL_IPATYPE and its index in the caller as the jump function 
         of this argument.  */
      if (TREE_CODE (TREE_VALUE (arg)) == PARM_DECL)
	{
	  mt = ipa_callsite_caller (cs);
	  i = ipa_method_tree_map (mt, TREE_VALUE (arg));
	  if (i < 0 || ipa_method_is_modified (mt, i))
	    ipa_callsite_param_set_type (cs, arg_num, UNKNOWN_IPATYPE);
	  else
	    {
	      ipa_callsite_param_set_type (cs, arg_num, FORMAL_IPATYPE);
	      ipa_callsite_param_set_info_type_formal (cs, arg_num, i);
	    }
	}
      /* If a constant value was passed as argument, 
         we store CONST_IPATYPE and its value as the jump function 
         of this argument.  */
      else if (TREE_CODE (TREE_VALUE (arg)) == INTEGER_CST
	       || TREE_CODE (TREE_VALUE (arg)) == REAL_CST)
	{
	  ipa_callsite_param_set_type (cs, arg_num, CONST_IPATYPE);
	  ipa_callsite_param_set_info_type (cs, arg_num,
					    TREE_VALUE (arg));
	}
      /* This is for the case of Fortran. If the address of a const_decl 
         was passed as argument then we store 
         CONST_IPATYPE_REF/CONST_IPATYPE_REF and the constant 
         value as the jump function corresponding to this argument.  */
      else if (TREE_CODE (TREE_VALUE (arg)) == ADDR_EXPR
	       && TREE_CODE (TREE_OPERAND (TREE_VALUE (arg), 0)) ==
	       CONST_DECL)
	{
	  cst_decl = TREE_OPERAND (TREE_VALUE (arg), 0);
	  if (TREE_CODE (DECL_INITIAL (cst_decl)) == INTEGER_CST
	      || TREE_CODE (DECL_INITIAL (cst_decl)) == REAL_CST)
	    {
	      ipa_callsite_param_set_type (cs, arg_num,
					   CONST_IPATYPE_REF);
	      ipa_callsite_param_set_info_type (cs, arg_num,
						DECL_INITIAL (cst_decl));
	    }
	}
      else
	ipa_callsite_param_set_type (cs, arg_num, UNKNOWN_IPATYPE);
      arg_num++;
    }
}