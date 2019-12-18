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
 int /*<<< orphan*/  pop_target () ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 scalar_t__ sr_get_debug () ; 
 char* target_shortname ; 

__attribute__((used)) static void
gdbsim_detach (char *args, int from_tty)
{
  if (sr_get_debug ())
    printf_filtered ("gdbsim_detach: args \"%s\"\n", args);

  pop_target ();		/* calls gdbsim_close to do the real work */
  if (from_tty)
    printf_filtered ("Ending simulator %s debugging\n", target_shortname);
}