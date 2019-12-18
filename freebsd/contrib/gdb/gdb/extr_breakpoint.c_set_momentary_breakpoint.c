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
struct symtab_and_line {int dummy; } ;
struct frame_id {int dummy; } ;
struct breakpoint {int /*<<< orphan*/  thread; struct frame_id frame_id; int /*<<< orphan*/  disposition; int /*<<< orphan*/  enable_state; } ;
typedef  enum bptype { ____Placeholder_bptype } bptype ;

/* Variables and functions */
 int /*<<< orphan*/  bp_enabled ; 
 int /*<<< orphan*/  disp_donttouch ; 
 scalar_t__ in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_thread_id (int /*<<< orphan*/ ) ; 
 struct breakpoint* set_raw_breakpoint (struct symtab_and_line,int) ; 

struct breakpoint *
set_momentary_breakpoint (struct symtab_and_line sal, struct frame_id frame_id,
			  enum bptype type)
{
  struct breakpoint *b;
  b = set_raw_breakpoint (sal, type);
  b->enable_state = bp_enabled;
  b->disposition = disp_donttouch;
  b->frame_id = frame_id;

  /* If we're debugging a multi-threaded program, then we
     want momentary breakpoints to be active in only a 
     single thread of control.  */
  if (in_thread_list (inferior_ptid))
    b->thread = pid_to_thread_id (inferior_ptid);

  return b;
}