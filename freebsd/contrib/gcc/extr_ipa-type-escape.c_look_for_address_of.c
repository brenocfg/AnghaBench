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
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ ARRAY_REF ; 
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DECL_FIELD_CONTEXT (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ get_base_var (scalar_t__) ; 
 int /*<<< orphan*/  get_canon_type (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  has_proper_scope_for_analysis (scalar_t__) ; 
 int /*<<< orphan*/  mark_interesting_addressof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
look_for_address_of (tree t)
{
  if (TREE_CODE (t) == ADDR_EXPR)
    {
      tree x = get_base_var (t);
      tree cref = TREE_OPERAND (t, 0);

      /* If we have an expression of the form "&a.b.c.d", mark a.b,
	 b.c and c.d. as having its address taken.  */ 
      tree fielddecl = NULL_TREE;
      while (cref!= x)
	{
	  if (TREE_CODE (cref) == COMPONENT_REF)
	    {
	      fielddecl =  TREE_OPERAND (cref, 1);
	      mark_interesting_addressof (TREE_TYPE (fielddecl), 
					  DECL_FIELD_CONTEXT (fielddecl));
	    }
	  else if (TREE_CODE (cref) == ARRAY_REF)
	    get_canon_type (TREE_TYPE (cref), false, false);

	  cref = TREE_OPERAND (cref, 0);
	}

      if (TREE_CODE (x) == VAR_DECL) 
	has_proper_scope_for_analysis (x);
    }
}