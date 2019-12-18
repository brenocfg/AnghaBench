#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int insns; struct cgraph_node* inlined_to; } ;
struct TYPE_3__ {int self_insns; } ;
struct cgraph_node {TYPE_2__ global; TYPE_1__ local; struct cgraph_edge* callees; } ;
struct cgraph_edge {struct cgraph_node* callee; struct cgraph_edge* next_callee; } ;

/* Variables and functions */
 char* N_ (char*) ; 
 int /*<<< orphan*/  PARAM_LARGE_FUNCTION_GROWTH ; 
 int /*<<< orphan*/  PARAM_LARGE_FUNCTION_INSNS ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int cgraph_estimate_size_after_inlining (int,struct cgraph_node*,struct cgraph_node*) ; 

__attribute__((used)) static bool
cgraph_check_inline_limits (struct cgraph_node *to, struct cgraph_node *what,
			    const char **reason, bool one_only)
{
  int times = 0;
  struct cgraph_edge *e;
  int newsize;
  int limit;

  if (one_only)
    times = 1;
  else
    for (e = to->callees; e; e = e->next_callee)
      if (e->callee == what)
	times++;

  if (to->global.inlined_to)
    to = to->global.inlined_to;

  /* When inlining large function body called once into small function,
     take the inlined function as base for limiting the growth.  */
  if (to->local.self_insns > what->local.self_insns)
    limit = to->local.self_insns;
  else
    limit = what->local.self_insns;

  limit += limit * PARAM_VALUE (PARAM_LARGE_FUNCTION_GROWTH) / 100;

  /* Check the size after inlining against the function limits.  But allow
     the function to shrink if it went over the limits by forced inlining.  */
  newsize = cgraph_estimate_size_after_inlining (times, to, what);
  if (newsize >= to->global.insns
      && newsize > PARAM_VALUE (PARAM_LARGE_FUNCTION_INSNS)
      && newsize > limit)
    {
      if (reason)
        *reason = N_("--param large-function-growth limit reached");
      return false;
    }
  return true;
}