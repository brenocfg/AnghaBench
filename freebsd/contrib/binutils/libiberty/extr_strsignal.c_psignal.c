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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  init_signal_tables () ; 
 int /*<<< orphan*/ * signal_names ; 
 int /*<<< orphan*/  stderr ; 
 int sys_nsig ; 
 char** sys_siglist ; 

void
psignal (int signo, char *message)
{
  if (signal_names == NULL)
    {
      init_signal_tables ();
    }
  if ((signo <= 0) || (signo >= sys_nsig))
    {
      fprintf (stderr, "%s: unknown signal\n", message);
    }
  else
    {
      fprintf (stderr, "%s: %s\n", message, sys_siglist[signo]);
    }
}