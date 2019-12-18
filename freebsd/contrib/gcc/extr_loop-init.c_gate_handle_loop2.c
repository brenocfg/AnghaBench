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
 scalar_t__ HAVE_doloop_end ; 
 scalar_t__ flag_branch_on_count_reg ; 
 scalar_t__ flag_move_loop_invariants ; 
 scalar_t__ flag_peel_loops ; 
 scalar_t__ flag_unroll_loops ; 
 scalar_t__ flag_unswitch_loops ; 
 scalar_t__ optimize ; 

__attribute__((used)) static bool
gate_handle_loop2 (void)
{
  return (optimize > 0
  	  && (flag_move_loop_invariants
              || flag_unswitch_loops
              || flag_peel_loops
              || flag_unroll_loops
#ifdef HAVE_doloop_end
	      || (flag_branch_on_count_reg && HAVE_doloop_end)
#endif
	      ));
}