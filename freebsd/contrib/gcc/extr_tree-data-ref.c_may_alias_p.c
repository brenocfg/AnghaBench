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
typedef  int /*<<< orphan*/  tree ;
struct data_reference {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptr_decl_may_alias_p (int /*<<< orphan*/ ,scalar_t__,struct data_reference*,int*) ; 
 int ptr_ptr_may_alias_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct data_reference*,struct data_reference*,int*) ; 

__attribute__((used)) static bool
may_alias_p (tree base_a, tree base_b,
	     struct data_reference *dra,
	     struct data_reference *drb,
	     bool *aliased)
{
  if (TREE_CODE (base_a) == ADDR_EXPR || TREE_CODE (base_b) == ADDR_EXPR)
    {
      if (TREE_CODE (base_a) == ADDR_EXPR && TREE_CODE (base_b) == ADDR_EXPR)
	{
	 *aliased = (TREE_OPERAND (base_a, 0) == TREE_OPERAND (base_b, 0));
	 return true;
	}
      if (TREE_CODE (base_a) == ADDR_EXPR)
	return ptr_decl_may_alias_p (base_b, TREE_OPERAND (base_a, 0), drb, 
				     aliased);
      else
	return ptr_decl_may_alias_p (base_a, TREE_OPERAND (base_b, 0), dra, 
				     aliased);
    }

  return ptr_ptr_may_alias_p (base_a, base_b, dra, drb, aliased);
}