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
struct frame_info {int dummy; } ;
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax_print (int /*<<< orphan*/ ,struct agent_expr*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct agent_expr* gen_trace_for_expr (int /*<<< orphan*/ ,struct expression*) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 int /*<<< orphan*/  make_cleanup_free_agent_expr (struct agent_expr*) ; 
 scalar_t__ overlay_debugging ; 
 struct expression* parse_expression (char*) ; 

__attribute__((used)) static void
agent_command (char *exp, int from_tty)
{
  struct cleanup *old_chain = 0;
  struct expression *expr;
  struct agent_expr *agent;
  struct frame_info *fi = get_current_frame ();	/* need current scope */

  /* We don't deal with overlay debugging at the moment.  We need to
     think more carefully about this.  If you copy this code into
     another command, change the error message; the user shouldn't
     have to know anything about agent expressions.  */
  if (overlay_debugging)
    error ("GDB can't do agent expression translation with overlays.");

  if (exp == 0)
    error_no_arg ("expression to translate");

  expr = parse_expression (exp);
  old_chain = make_cleanup (free_current_contents, &expr);
  agent = gen_trace_for_expr (get_frame_pc (fi), expr);
  make_cleanup_free_agent_expr (agent);
  ax_print (gdb_stdout, agent);

  /* It would be nice to call ax_reqs here to gather some general info
     about the expression, and then print out the result.  */

  do_cleanups (old_chain);
  dont_repeat ();
}