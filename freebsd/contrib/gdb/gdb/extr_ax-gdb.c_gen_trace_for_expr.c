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
typedef  union exp_element {int dummy; } exp_element ;
struct expression {union exp_element* elts; } ;
struct cleanup {int dummy; } ;
struct axs_value {int dummy; } ;
struct agent_expr {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  aop_end ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  gen_expr (union exp_element**,struct agent_expr*,struct axs_value*) ; 
 int /*<<< orphan*/  gen_traced_pop (struct agent_expr*,struct axs_value*) ; 
 struct cleanup* make_cleanup_free_agent_expr (struct agent_expr*) ; 
 struct agent_expr* new_agent_expr (int /*<<< orphan*/ ) ; 
 int trace_kludge ; 

struct agent_expr *
gen_trace_for_expr (CORE_ADDR scope, struct expression *expr)
{
  struct cleanup *old_chain = 0;
  struct agent_expr *ax = new_agent_expr (scope);
  union exp_element *pc;
  struct axs_value value;

  old_chain = make_cleanup_free_agent_expr (ax);

  pc = expr->elts;
  trace_kludge = 1;
  gen_expr (&pc, ax, &value);

  /* Make sure we record the final object, and get rid of it.  */
  gen_traced_pop (ax, &value);

  /* Oh, and terminate.  */
  ax_simple (ax, aop_end);

  /* We have successfully built the agent expr, so cancel the cleanup
     request.  If we add more cleanups that we always want done, this
     will have to get more complicated.  */
  discard_cleanups (old_chain);
  return ax;
}