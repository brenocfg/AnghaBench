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
 scalar_t__ SIM_RC_FAIL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdbsim_desc ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 int program_loaded ; 
 scalar_t__ sim_load (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sr_get_debug () ; 

__attribute__((used)) static void
gdbsim_load (char *prog, int fromtty)
{
  if (sr_get_debug ())
    printf_filtered ("gdbsim_load: prog \"%s\"\n", prog);

  inferior_ptid = null_ptid;

  /* FIXME: We will print two messages on error.
     Need error to either not print anything if passed NULL or need
     another routine that doesn't take any arguments.  */
  if (sim_load (gdbsim_desc, prog, NULL, fromtty) == SIM_RC_FAIL)
    error ("unable to load program");

  /* FIXME: If a load command should reset the targets registers then
     a call to sim_create_inferior() should go here. */

  program_loaded = 1;
}