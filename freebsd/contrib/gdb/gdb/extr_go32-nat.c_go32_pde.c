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
 int /*<<< orphan*/  display_ptable_entry (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,long) ; 
 int /*<<< orphan*/  get_cr3 () ; 
 int /*<<< orphan*/  get_pde (long) ; 
 scalar_t__ isspace (char) ; 
 long parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  pdbr ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
go32_pde (char *arg, int from_tty)
{
  long pde_idx = -1, i;

  if (arg && *arg)
    {
      while (*arg && isspace(*arg))
	arg++;

      if (*arg)
	{
	  pde_idx = parse_and_eval_long (arg);
	  if (pde_idx < 0 || pde_idx >= 1024)
	    error ("Entry %ld is outside valid limits [0..1023].", pde_idx);
	}
    }

  pdbr = get_cr3 ();
  if (!pdbr)
    puts_filtered ("Access to Page Directories is not supported on this system.\n");
  else if (pde_idx >= 0)
    display_ptable_entry (get_pde (pde_idx), 1, 1, 0);
  else
    for (i = 0; i < 1024; i++)
      display_ptable_entry (get_pde (i), 1, 0, 0);
}