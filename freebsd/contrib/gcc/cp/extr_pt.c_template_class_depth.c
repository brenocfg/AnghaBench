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
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_INFO (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TI_ARGS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 scalar_t__ uses_template_parms (int /*<<< orphan*/ ) ; 

int
template_class_depth (tree type)
{
  int depth;

  for (depth = 0;
       type && TREE_CODE (type) != NAMESPACE_DECL;
       type = (TREE_CODE (type) == FUNCTION_DECL)
	 ? CP_DECL_CONTEXT (type) : TYPE_CONTEXT (type))
    {
      if (TREE_CODE (type) != FUNCTION_DECL)
	{
	  if (CLASSTYPE_TEMPLATE_INFO (type)
	      && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (type))
	      && uses_template_parms (CLASSTYPE_TI_ARGS (type)))
	    ++depth;
	}
      else
	{
	  if (DECL_TEMPLATE_INFO (type)
	      && PRIMARY_TEMPLATE_P (DECL_TI_TEMPLATE (type))
	      && uses_template_parms (DECL_TI_ARGS (type)))
	    ++depth;
	}
    }

  return depth;
}