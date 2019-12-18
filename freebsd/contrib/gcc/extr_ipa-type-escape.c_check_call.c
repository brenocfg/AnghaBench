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
typedef  enum availability { ____Placeholder_availability } availability ;

/* Variables and functions */
 int AVAIL_NOT_AVAILABLE ; 
 int AVAIL_OVERWRITABLE ; 
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 int ECF_MALLOC ; 
 int /*<<< orphan*/  EXPOSED_PARAMETER ; 
 int /*<<< orphan*/  FULL_ESCAPE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int call_expr_flags (scalar_t__) ; 
 int cgraph_function_body_availability (struct cgraph_node*) ; 
 struct cgraph_node* cgraph_node (scalar_t__) ; 
 int /*<<< orphan*/  check_cast (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  check_rhs_var (scalar_t__) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 
 int /*<<< orphan*/  mark_interesting_type (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static bool
check_call (tree call_expr) 
{
  int flags = call_expr_flags(call_expr);
  tree operand_list = TREE_OPERAND (call_expr, 1);
  tree operand;
  tree callee_t = get_callee_fndecl (call_expr);
  tree argument;
  struct cgraph_node* callee;
  enum availability avail = AVAIL_NOT_AVAILABLE;

  for (operand = operand_list;
       operand != NULL_TREE;
       operand = TREE_CHAIN (operand))
    {
      tree argument = TREE_VALUE (operand);
      check_rhs_var (argument);
    }
  
  if (callee_t)
    {
      tree arg_type;
      tree last_arg_type = NULL;
      callee = cgraph_node(callee_t);
      avail = cgraph_function_body_availability (callee);
      
      /* Check that there are no implicit casts in the passing of
	 parameters.  */
      if (TYPE_ARG_TYPES (TREE_TYPE (callee_t)))
	{
	  operand = operand_list;
	  for (arg_type = TYPE_ARG_TYPES (TREE_TYPE (callee_t));
	       arg_type && TREE_VALUE (arg_type) != void_type_node;
	       arg_type = TREE_CHAIN (arg_type))
	    {
	      if (operand)
		{
		  argument = TREE_VALUE (operand);
		  last_arg_type = TREE_VALUE(arg_type);
		  check_cast (last_arg_type, argument);
		  operand = TREE_CHAIN (operand);
		}
	      else 
		/* The code reaches here for some unfortunate
		   builtin functions that do not have a list of
		   argument types.  */
		break; 
	    }
	} 
      else  
	{ 
	  /* FIXME - According to Geoff Keating, we should never
	     have to do this; the front ends should always process
	     the arg list from the TYPE_ARG_LIST. */
	  operand = operand_list;
	  for (arg_type = DECL_ARGUMENTS (callee_t); 
	       arg_type;
	       arg_type = TREE_CHAIN (arg_type))
	    {
	      if (operand)
		{
		  argument = TREE_VALUE (operand);
		  last_arg_type = TREE_TYPE(arg_type);
		  check_cast (last_arg_type, argument);
		  operand = TREE_CHAIN (operand);
		} 
	      else 
		/* The code reaches here for some unfortunate
		   builtin functions that do not have a list of
		   argument types.  */
		break; 
	    }
	}
      
      /* In the case where we have a var_args function, we need to
	 check the remaining parameters against the last argument.  */
      arg_type = last_arg_type;
      for (;
	   operand != NULL_TREE;
	   operand = TREE_CHAIN (operand))
	{
	  argument = TREE_VALUE (operand);
	  if (arg_type)
	    check_cast (arg_type, argument);
	  else 
	    {
	      /* The code reaches here for some unfortunate
		 builtin functions that do not have a list of
		 argument types.  Most of these functions have
		 been marked as having their parameters not
		 escape, but for the rest, the type is doomed.  */
	      tree type = get_canon_type (TREE_TYPE (argument), false, false);
	      mark_interesting_type (type, FULL_ESCAPE);
	    }
	}
    }

  /* The callee is either unknown (indirect call) or there is just no
     scannable code for it (external call) .  We look to see if there
     are any bits available for the callee (such as by declaration or
     because it is builtin) and process solely on the basis of those
     bits. */

  if (avail == AVAIL_NOT_AVAILABLE || avail == AVAIL_OVERWRITABLE)
    {
      /* If this is a direct call to an external function, mark all of
	 the parameter and return types.  */
      for (operand = operand_list;
	   operand != NULL_TREE;
	   operand = TREE_CHAIN (operand))
	{
	  tree type = 
	    get_canon_type (TREE_TYPE (TREE_VALUE (operand)), false, false);
	  mark_interesting_type (type, EXPOSED_PARAMETER);
    }
	  
      if (callee_t) 
	{
	  tree type = 
	    get_canon_type (TREE_TYPE (TREE_TYPE (callee_t)), false, false);
	  mark_interesting_type (type, EXPOSED_PARAMETER);
	}
    }
  return (flags & ECF_MALLOC);
}