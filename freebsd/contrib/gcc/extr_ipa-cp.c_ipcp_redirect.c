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
struct ipa_jump_func {int dummy; } ;
struct cgraph_node {int dummy; } ;
struct cgraph_edge {struct cgraph_node* callee; struct cgraph_node* caller; } ;
typedef  enum jump_func_type { ____Placeholder_jump_func_type } jump_func_type ;
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;

/* Variables and functions */
 int CONST_IPATYPE ; 
 int CONST_IPATYPE_REF ; 
 int get_type (struct ipa_jump_func*) ; 
 struct ipa_jump_func* ipa_callsite_param (struct cgraph_edge*,int) ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 
 int ipcp_cval_get_cvalue_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_method_cval (struct cgraph_node*,int) ; 
 struct cgraph_node* ipcp_method_orig_node (struct cgraph_node*) ; 
 scalar_t__ ipcp_type_is_const (int) ; 

__attribute__((used)) static bool
ipcp_redirect (struct cgraph_edge *cs)
{
  struct cgraph_node *caller, *callee, *orig_callee;
  int i, count;
  struct ipa_jump_func *jump_func;
  enum jump_func_type type;
  enum cvalue_type cval_type;

  caller = cs->caller;
  callee = cs->callee;
  orig_callee = ipcp_method_orig_node (callee);
  count = ipa_method_formal_count (orig_callee);
  for (i = 0; i < count; i++)
    {
      cval_type =
	ipcp_cval_get_cvalue_type (ipcp_method_cval (orig_callee, i));
      if (ipcp_type_is_const (cval_type))
	{
	  jump_func = ipa_callsite_param (cs, i);
	  type = get_type (jump_func);
	  if (type != CONST_IPATYPE 
	      && type != CONST_IPATYPE_REF)
	    return true;
	}
    }

  return false;
}