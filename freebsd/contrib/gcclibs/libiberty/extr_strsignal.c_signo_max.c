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
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_signal_tables () ; 
 int /*<<< orphan*/  num_signal_names ; 
 int /*<<< orphan*/ * signal_names ; 
 int /*<<< orphan*/  sys_nsig ; 

int
signo_max (void)
{
  int maxsize;

  if (signal_names == NULL)
    {
      init_signal_tables ();
    }
  maxsize = MAX (sys_nsig, num_signal_names);
  return (maxsize - 1);
}