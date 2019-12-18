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
struct mem_address {int /*<<< orphan*/  symbol; } ;
struct affine_tree_combination {unsigned int n; int* coefs; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aff_combination_remove_elt (struct affine_tree_combination*,unsigned int) ; 
 scalar_t__ fixed_address_object_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
move_fixed_address_to_symbol (struct mem_address *parts,
			      struct affine_tree_combination *addr)
{
  unsigned i;
  tree val = NULL_TREE;

  for (i = 0; i < addr->n; i++)
    {
      if (addr->coefs[i] != 1)
	continue;

      val = addr->elts[i];
      if (TREE_CODE (val) == ADDR_EXPR
	  && fixed_address_object_p (TREE_OPERAND (val, 0)))
	break;
    }

  if (i == addr->n)
    return;

  parts->symbol = TREE_OPERAND (val, 0);
  aff_combination_remove_elt (addr, i);
}