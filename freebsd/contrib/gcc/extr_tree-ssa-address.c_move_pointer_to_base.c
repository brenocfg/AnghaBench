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
struct mem_address {int /*<<< orphan*/  base; } ;
struct affine_tree_combination {unsigned int n; int* coefs; int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aff_combination_remove_elt (struct affine_tree_combination*,unsigned int) ; 

__attribute__((used)) static void
move_pointer_to_base (struct mem_address *parts,
		      struct affine_tree_combination *addr)
{
  unsigned i;
  tree val = NULL_TREE;

  for (i = 0; i < addr->n; i++)
    {
      if (addr->coefs[i] != 1)
	continue;

      val = addr->elts[i];
      if (POINTER_TYPE_P (TREE_TYPE (val)))
	break;
    }

  if (i == addr->n)
    return;

  parts->base = val;
  aff_combination_remove_elt (addr, i);
}