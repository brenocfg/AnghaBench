#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int num_breakpoints; int /*<<< orphan*/ * clr_break; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ADDR_BITS_REMOVE (scalar_t__) ; 
 int MO_ADDR_BITS_REMOVE ; 
 int MO_CLR_BREAK_1_BASED ; 
 int MO_CLR_BREAK_USES_ADDR ; 
 scalar_t__* breakaddr ; 
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  monitor_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  paddr (scalar_t__) ; 
 int /*<<< orphan*/  paddr_nz (scalar_t__) ; 

__attribute__((used)) static int
monitor_remove_breakpoint (CORE_ADDR addr, char *shadow)
{
  int i;

  monitor_debug ("MON rmbkpt %s\n", paddr (addr));
  if (current_monitor->clr_break == NULL)
    error ("No clr_break defined for this monitor");

  if (current_monitor->flags & MO_ADDR_BITS_REMOVE)
    addr = ADDR_BITS_REMOVE (addr);

  for (i = 0; i < current_monitor->num_breakpoints; i++)
    {
      if (breakaddr[i] == addr)
	{
	  breakaddr[i] = 0;
	  /* some monitors remove breakpoints based on the address */
	  if (current_monitor->flags & MO_CLR_BREAK_USES_ADDR)
	    monitor_printf (current_monitor->clr_break, addr);
	  else if (current_monitor->flags & MO_CLR_BREAK_1_BASED)
	    monitor_printf (current_monitor->clr_break, i + 1);
	  else
	    monitor_printf (current_monitor->clr_break, i);
	  monitor_expect_prompt (NULL, 0);
	  return 0;
	}
    }
  fprintf_unfiltered (gdb_stderr,
		      "Can't find breakpoint associated with 0x%s\n",
		      paddr_nz (addr));
  return 1;
}