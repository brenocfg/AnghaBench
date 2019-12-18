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
 int /*<<< orphan*/  end_callbacks () ; 
 int /*<<< orphan*/ * gdbsim_desc ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 scalar_t__ program_loaded ; 
 int /*<<< orphan*/  sim_close (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sr_get_debug () ; 

__attribute__((used)) static void
gdbsim_close (int quitting)
{
  if (sr_get_debug ())
    printf_filtered ("gdbsim_close: quitting %d\n", quitting);

  program_loaded = 0;

  if (gdbsim_desc != NULL)
    {
      sim_close (gdbsim_desc, quitting);
      gdbsim_desc = NULL;
    }

  end_callbacks ();
  generic_mourn_inferior ();
}