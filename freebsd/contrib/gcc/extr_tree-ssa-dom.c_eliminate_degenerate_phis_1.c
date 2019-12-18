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
typedef  int /*<<< orphan*/  bitmap ;
typedef  scalar_t__ basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  eliminate_const_or_copy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ first_dom_son (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ next_dom_son (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ phi_nodes (scalar_t__) ; 

__attribute__((used)) static void
eliminate_degenerate_phis_1 (basic_block bb, bitmap interesting_names)
{
  tree phi, next;
  basic_block son;

  for (phi = phi_nodes (bb); phi; phi = next)
    {
      next = PHI_CHAIN (phi);
      eliminate_const_or_copy (phi, interesting_names);
    }

  /* Recurse into the dominator children of BB.  */
  for (son = first_dom_son (CDI_DOMINATORS, bb);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    eliminate_degenerate_phis_1 (son, interesting_names);
}