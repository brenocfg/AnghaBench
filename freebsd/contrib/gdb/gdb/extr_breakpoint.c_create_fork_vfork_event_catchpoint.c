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
struct symtab_and_line {scalar_t__ line; int /*<<< orphan*/ * symtab; scalar_t__ pc; } ;
struct breakpoint {int thread; scalar_t__ forked_inferior_pid; int /*<<< orphan*/  disposition; int /*<<< orphan*/  enable_state; int /*<<< orphan*/ * addr_string; int /*<<< orphan*/ * cond_string; int /*<<< orphan*/ * cond; scalar_t__ number; } ;
typedef  enum bptype { ____Placeholder_bptype } bptype ;

/* Variables and functions */
 int /*<<< orphan*/  bp_enabled ; 
 scalar_t__ breakpoint_count ; 
 int /*<<< orphan*/  disp_del ; 
 int /*<<< orphan*/  disp_donttouch ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 int /*<<< orphan*/  mention (struct breakpoint*) ; 
 int /*<<< orphan*/ * savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_breakpoint_count (scalar_t__) ; 
 struct breakpoint* set_raw_breakpoint (struct symtab_and_line,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
create_fork_vfork_event_catchpoint (int tempflag, char *cond_string,
				    enum bptype bp_kind)
{
  struct symtab_and_line sal;
  struct breakpoint *b;
  int thread = -1;		/* All threads. */

  init_sal (&sal);
  sal.pc = 0;
  sal.symtab = NULL;
  sal.line = 0;

  b = set_raw_breakpoint (sal, bp_kind);
  set_breakpoint_count (breakpoint_count + 1);
  b->number = breakpoint_count;
  b->cond = NULL;
  b->cond_string = (cond_string == NULL) ? 
    NULL : savestring (cond_string, strlen (cond_string));
  b->thread = thread;
  b->addr_string = NULL;
  b->enable_state = bp_enabled;
  b->disposition = tempflag ? disp_del : disp_donttouch;
  b->forked_inferior_pid = 0;

  mention (b);
}