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
 scalar_t__ flag_non_call_exceptions ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  purge_all_dead_edges () ; 
 int /*<<< orphan*/  reload_cse_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_postreload (void)
{
  /* Do a very simple CSE pass over just the hard registers.  */
  reload_cse_regs (get_insns ());
  /* reload_cse_regs can eliminate potentially-trapping MEMs.
     Remove any EH edges associated with them.  */
  if (flag_non_call_exceptions)
    purge_all_dead_edges ();
  return 0;
}