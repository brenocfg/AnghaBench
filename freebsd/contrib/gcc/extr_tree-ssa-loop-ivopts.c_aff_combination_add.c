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
struct affine_tree_combination {int offset; int mask; unsigned int n; int* coefs; scalar_t__ rest; scalar_t__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  aff_combination_add_elt (struct affine_tree_combination*,scalar_t__,int) ; 

__attribute__((used)) static void
aff_combination_add (struct affine_tree_combination *comb1,
		     struct affine_tree_combination *comb2)
{
  unsigned i;

  comb1->offset = (comb1->offset + comb2->offset) & comb1->mask;
  for (i = 0; i < comb2->n; i++)
    aff_combination_add_elt (comb1, comb2->elts[i], comb2->coefs[i]);
  if (comb2->rest)
    aff_combination_add_elt (comb1, comb2->rest, 1);
}