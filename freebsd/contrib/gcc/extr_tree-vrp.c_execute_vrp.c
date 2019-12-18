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

/* Variables and functions */
 int /*<<< orphan*/  LOOPS_NORMAL ; 
 int /*<<< orphan*/  TODO_update_ssa ; 
 int /*<<< orphan*/ * current_loops ; 
 int /*<<< orphan*/  finalize_jump_threads () ; 
 int /*<<< orphan*/  insert_range_assertions () ; 
 int /*<<< orphan*/  loop_optimizer_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loop_optimizer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_range_assertions () ; 
 int /*<<< orphan*/  scev_finalize () ; 
 int /*<<< orphan*/  scev_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssa_propagate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ssa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrp_finalize () ; 
 int /*<<< orphan*/  vrp_initialize () ; 
 int /*<<< orphan*/  vrp_visit_phi_node ; 
 int /*<<< orphan*/  vrp_visit_stmt ; 

__attribute__((used)) static unsigned int
execute_vrp (void)
{
  insert_range_assertions ();

  current_loops = loop_optimizer_init (LOOPS_NORMAL);
  if (current_loops)
    scev_initialize (current_loops);

  vrp_initialize ();
  ssa_propagate (vrp_visit_stmt, vrp_visit_phi_node);
  vrp_finalize ();

  if (current_loops)
    {
      scev_finalize ();
      loop_optimizer_finalize (current_loops);
      current_loops = NULL;
    }

  /* ASSERT_EXPRs must be removed before finalizing jump threads
     as finalizing jump threads calls the CFG cleanup code which
     does not properly handle ASSERT_EXPRs.  */
  remove_range_assertions ();

  /* If we exposed any new variables, go ahead and put them into
     SSA form now, before we handle jump threading.  This simplifies
     interactions between rewriting of _DECL nodes into SSA form
     and rewriting SSA_NAME nodes into SSA form after block
     duplication and CFG manipulation.  */
  update_ssa (TODO_update_ssa);

  finalize_jump_threads ();
  return 0;
}