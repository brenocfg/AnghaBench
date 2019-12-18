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
 scalar_t__ CP_TYPE_CONST_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_FUNCTION_MEMBER_P (scalar_t__) ; 
 scalar_t__ DECL_MEMBER_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_FIRST_USER_PARMTYPE (scalar_t__) ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ void_list_node ; 

int
copy_fn_p (tree d)
{
  tree args;
  tree arg_type;
  int result = 1;

  gcc_assert (DECL_FUNCTION_MEMBER_P (d));

  if (TREE_CODE (d) == TEMPLATE_DECL
      || (DECL_TEMPLATE_INFO (d)
	  && DECL_MEMBER_TEMPLATE_P (DECL_TI_TEMPLATE (d))))
    /* Instantiations of template member functions are never copy
       functions.  Note that member functions of templated classes are
       represented as template functions internally, and we must
       accept those as copy functions.  */
    return 0;

  args = FUNCTION_FIRST_USER_PARMTYPE (d);
  if (!args)
    return 0;

  arg_type = TREE_VALUE (args);
  if (arg_type == error_mark_node)
    return 0;

  if (TYPE_MAIN_VARIANT (arg_type) == DECL_CONTEXT (d))
    {
      /* Pass by value copy assignment operator.  */
      result = -1;
    }
  else if (TREE_CODE (arg_type) == REFERENCE_TYPE
	   && TYPE_MAIN_VARIANT (TREE_TYPE (arg_type)) == DECL_CONTEXT (d))
    {
      if (CP_TYPE_CONST_P (TREE_TYPE (arg_type)))
	result = 2;
    }
  else
    return 0;

  args = TREE_CHAIN (args);

  if (args && args != void_list_node && !TREE_PURPOSE (args))
    /* There are more non-optional args.  */
    return 0;

  return result;
}