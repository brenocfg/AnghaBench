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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_RESET ; 
 int /*<<< orphan*/  PR_RLC ; 
 int proc_modify_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_unset_run_on_last_close (procinfo *pi)
{
  return proc_modify_flag (pi, PR_RLC, FLAG_RESET);
}