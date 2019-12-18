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
 scalar_t__ BIT_FIELD_REF ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VIEW_CONVERT_EXPR ; 
 int /*<<< orphan*/  check_cast (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_base_address (scalar_t__) ; 
 int /*<<< orphan*/  get_canon_type (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ is_gimple_cast (scalar_t__) ; 

__attribute__((used)) static void 
look_for_casts (tree lhs __attribute__((unused)), tree t)
{
  if (is_gimple_cast (t) || TREE_CODE (t) == VIEW_CONVERT_EXPR)
    {
      tree castfromvar = TREE_OPERAND (t, 0);
      check_cast (TREE_TYPE (t), castfromvar);
    }
  else if (TREE_CODE (t) == COMPONENT_REF
	   || TREE_CODE (t) == INDIRECT_REF
	   || TREE_CODE (t) == BIT_FIELD_REF)
    {
      tree base = get_base_address (t);
      while (t != base)
	{
	  t = TREE_OPERAND (t, 0);
	  if (TREE_CODE (t) == VIEW_CONVERT_EXPR)
	    {
	      /* This may be some part of a component ref.
		 IE it may be a.b.VIEW_CONVERT_EXPR<weird_type>(c).d, AFAIK.
		 castfromref will give you a.b.c, not a. */
	      tree castfromref = TREE_OPERAND (t, 0);
	      check_cast (TREE_TYPE (t), castfromref);
	    }
	  else if (TREE_CODE (t) == COMPONENT_REF)
	    get_canon_type (TREE_TYPE (TREE_OPERAND (t, 1)), false, false);
	}
    } 
}