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

/* Variables and functions */
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  gen_expr (union exp_element**,struct agent_expr*,struct axs_value*) ; 
 struct cleanup* make_cleanup_free_agent_expr (struct agent_expr*) ; 
 struct agent_expr* new_agent_expr (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_kludge ; 

struct agent_expr *
expr_to_agent (struct expression *expr, struct axs_value *value)
{
  struct cleanup *old_chain = 0;
  struct agent_expr *ax = new_agent_expr (0);
  union exp_element *pc;

  old_chain = make_cleanup_free_agent_expr (ax);

  pc = expr->elts;
  trace_kludge = 0;
  gen_expr (&pc, ax, value);

  /* We have successfully built the agent expr, so cancel the cleanup
     request.  If we add more cleanups that we always want done, this
     will have to get more complicated.  */
  discard_cleanups (old_chain);
  return ax;
}