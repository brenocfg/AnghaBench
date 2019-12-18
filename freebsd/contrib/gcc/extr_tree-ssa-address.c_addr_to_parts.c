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
struct mem_address {void* symbol; void* offset; void* step; void* index; void* base; } ;
struct affine_tree_combination {int offset; unsigned int n; int* coefs; scalar_t__ rest; scalar_t__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULT_EXPR ; 
 void* NULL_TREE ; 
 int /*<<< orphan*/  add_to_parts (struct mem_address*,int /*<<< orphan*/ ) ; 
 void* build_int_cst_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  most_expensive_mult_to_index (struct mem_address*,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  move_fixed_address_to_symbol (struct mem_address*,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  move_pointer_to_base (struct mem_address*,struct affine_tree_combination*) ; 
 int /*<<< orphan*/  sizetype ; 

__attribute__((used)) static void
addr_to_parts (struct affine_tree_combination *addr, struct mem_address *parts)
{
  unsigned i;
  tree part;

  parts->symbol = NULL_TREE;
  parts->base = NULL_TREE;
  parts->index = NULL_TREE;
  parts->step = NULL_TREE;

  if (addr->offset)
    parts->offset = build_int_cst_type (sizetype, addr->offset);
  else
    parts->offset = NULL_TREE;

  /* Try to find a symbol.  */
  move_fixed_address_to_symbol (parts, addr);

  /* First move the most expensive feasible multiplication
     to index.  */
  most_expensive_mult_to_index (parts, addr);

  /* Try to find a base of the reference.  Since at the moment
     there is no reliable way how to distinguish between pointer and its
     offset, this is just a guess.  */
  if (!parts->symbol)
    move_pointer_to_base (parts, addr);

  /* Then try to process the remaining elements.  */
  for (i = 0; i < addr->n; i++)
    {
      part = fold_convert (sizetype, addr->elts[i]);
      if (addr->coefs[i] != 1)
	part = fold_build2 (MULT_EXPR, sizetype, part,
			    build_int_cst_type (sizetype, addr->coefs[i]));
      add_to_parts (parts, part);
    }
  if (addr->rest)
    add_to_parts (parts, fold_convert (sizetype, addr->rest));
}