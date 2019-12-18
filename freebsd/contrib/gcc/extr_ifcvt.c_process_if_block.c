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
struct ce_if_block {scalar_t__ num_multiple_test_blocks; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ HAVE_conditional_execution ; 
 scalar_t__ HAVE_conditional_move ; 
 int TRUE ; 
 int /*<<< orphan*/  cancel_changes (int /*<<< orphan*/ ) ; 
 scalar_t__ cond_exec_process_if_block (struct ce_if_block*,int) ; 
 scalar_t__ cond_move_process_if_block (struct ce_if_block*) ; 
 scalar_t__ noce_process_if_block (struct ce_if_block*) ; 
 scalar_t__ reload_completed ; 

__attribute__((used)) static int
process_if_block (struct ce_if_block * ce_info)
{
  if (! reload_completed
      && noce_process_if_block (ce_info))
    return TRUE;

  if (HAVE_conditional_move
      && cond_move_process_if_block (ce_info))
    return TRUE;

  if (HAVE_conditional_execution && reload_completed)
    {
      /* If we have && and || tests, try to first handle combining the && and
         || tests into the conditional code, and if that fails, go back and
         handle it without the && and ||, which at present handles the && case
         if there was no ELSE block.  */
      if (cond_exec_process_if_block (ce_info, TRUE))
	return TRUE;

      if (ce_info->num_multiple_test_blocks)
	{
	  cancel_changes (0);

	  if (cond_exec_process_if_block (ce_info, FALSE))
	    return TRUE;
	}
    }

  return FALSE;
}