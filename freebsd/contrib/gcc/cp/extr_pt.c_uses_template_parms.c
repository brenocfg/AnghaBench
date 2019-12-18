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
 scalar_t__ BASELINK ; 
 scalar_t__ CONSTANT_CLASS_P (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ EXPR_P (scalar_t__) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ TEMPLATE_PARM_INDEX ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_LIST ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TREE_VEC ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int any_dependent_template_arguments_p (scalar_t__) ; 
 int dependent_type_p (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 
 scalar_t__ value_dependent_expression_p (scalar_t__) ; 

int
uses_template_parms (tree t)
{
  bool dependent_p;
  int saved_processing_template_decl;

  saved_processing_template_decl = processing_template_decl;
  if (!saved_processing_template_decl)
    processing_template_decl = 1;
  if (TYPE_P (t))
    dependent_p = dependent_type_p (t);
  else if (TREE_CODE (t) == TREE_VEC)
    dependent_p = any_dependent_template_arguments_p (t);
  else if (TREE_CODE (t) == TREE_LIST)
    dependent_p = (uses_template_parms (TREE_VALUE (t))
		   || uses_template_parms (TREE_CHAIN (t)));
  else if (TREE_CODE (t) == TYPE_DECL)
    dependent_p = dependent_type_p (TREE_TYPE (t));
  else if (DECL_P (t)
	   || EXPR_P (t)
	   || TREE_CODE (t) == TEMPLATE_PARM_INDEX
	   || TREE_CODE (t) == OVERLOAD
	   || TREE_CODE (t) == BASELINK
	   || TREE_CODE (t) == IDENTIFIER_NODE
	   || CONSTANT_CLASS_P (t))
    dependent_p = (type_dependent_expression_p (t)
		   || value_dependent_expression_p (t));
  else
    {
      gcc_assert (t == error_mark_node);
      dependent_p = false;
    }

  processing_template_decl = saved_processing_template_decl;

  return dependent_p;
}