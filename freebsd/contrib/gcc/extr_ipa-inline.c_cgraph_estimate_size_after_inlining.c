#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int insns; } ;
struct cgraph_node {TYPE_1__ global; scalar_t__ decl; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 int /*<<< orphan*/  PARAM_INLINE_CALL_COST ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ estimate_move_cost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static int
cgraph_estimate_size_after_inlining (int times, struct cgraph_node *to,
				     struct cgraph_node *what)
{
  int size;
  tree fndecl = what->decl, arg;
  int call_insns = PARAM_VALUE (PARAM_INLINE_CALL_COST);

  for (arg = DECL_ARGUMENTS (fndecl); arg; arg = TREE_CHAIN (arg))
    call_insns += estimate_move_cost (TREE_TYPE (arg));
  size = (what->global.insns - call_insns) * times + to->global.insns;
  gcc_assert (size >= 0);
  return size;
}