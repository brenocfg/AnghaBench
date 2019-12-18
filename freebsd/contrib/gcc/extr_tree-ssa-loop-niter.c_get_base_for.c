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
struct loop {int dummy; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_ARG_DEF_FROM_EDGE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ chain_of_csts_start (struct loop*,scalar_t__) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 int /*<<< orphan*/  loop_latch_edge (struct loop*) ; 
 int /*<<< orphan*/  loop_preheader_edge (struct loop*) ; 

__attribute__((used)) static tree
get_base_for (struct loop *loop, tree x)
{
  tree phi, init, next;

  if (is_gimple_min_invariant (x))
    return x;

  phi = chain_of_csts_start (loop, x);
  if (!phi)
    return NULL_TREE;

  init = PHI_ARG_DEF_FROM_EDGE (phi, loop_preheader_edge (loop));
  next = PHI_ARG_DEF_FROM_EDGE (phi, loop_latch_edge (loop));

  if (TREE_CODE (next) != SSA_NAME)
    return NULL_TREE;

  if (!is_gimple_min_invariant (init))
    return NULL_TREE;

  if (chain_of_csts_start (loop, next) != phi)
    return NULL_TREE;

  return phi;
}