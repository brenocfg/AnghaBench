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
 int /*<<< orphan*/  DECL_CLASS_TEMPLATE_P (scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_IDENTIFIER (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ constructor_name (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ get_type_value (scalar_t__) ; 
 int same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
check_dtor_name (tree basetype, tree name)
{
  /* Just accept something we've already complained about.  */
  if (name == error_mark_node)
    return true;

  if (TREE_CODE (name) == TYPE_DECL)
    name = TREE_TYPE (name);
  else if (TYPE_P (name))
    /* OK */;
  else if (TREE_CODE (name) == IDENTIFIER_NODE)
    {
      if ((IS_AGGR_TYPE (basetype) && name == constructor_name (basetype))
	  || (TREE_CODE (basetype) == ENUMERAL_TYPE
	      && name == TYPE_IDENTIFIER (basetype)))
	return true;
      else
	name = get_type_value (name);
    }
  else
    {
      /* In the case of:

	 template <class T> struct S { ~S(); };
	 int i;
	 i.~S();

	 NAME will be a class template.  */
      gcc_assert (DECL_CLASS_TEMPLATE_P (name));
      return false;
    }

  if (!name)
    return false;
  return same_type_p (TYPE_MAIN_VARIANT (basetype), TYPE_MAIN_VARIANT (name));
}