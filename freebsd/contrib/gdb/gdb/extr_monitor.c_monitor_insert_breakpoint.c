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
struct TYPE_2__ {int flags; int num_breakpoints; int /*<<< orphan*/ * set_break; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ADDR_BITS_REMOVE (scalar_t__) ; 
 int MO_ADDR_BITS_REMOVE ; 
 scalar_t__* breakaddr ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  error (char*,...) ; 
 unsigned char* gdbarch_breakpoint_from_pc (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  monitor_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  monitor_read_memory (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  paddr (scalar_t__) ; 

__attribute__((used)) static int
monitor_insert_breakpoint (CORE_ADDR addr, char *shadow)
{
  int i;
  const unsigned char *bp;
  int bplen;

  monitor_debug ("MON inst bkpt %s\n", paddr (addr));
  if (current_monitor->set_break == NULL)
    error ("No set_break defined for this monitor");

  if (current_monitor->flags & MO_ADDR_BITS_REMOVE)
    addr = ADDR_BITS_REMOVE (addr);

  /* Determine appropriate breakpoint size for this address.  */
  bp = gdbarch_breakpoint_from_pc (current_gdbarch, &addr, &bplen);

  for (i = 0; i < current_monitor->num_breakpoints; i++)
    {
      if (breakaddr[i] == 0)
	{
	  breakaddr[i] = addr;
	  monitor_read_memory (addr, shadow, bplen);
	  monitor_printf (current_monitor->set_break, addr);
	  monitor_expect_prompt (NULL, 0);
	  return 0;
	}
    }

  error ("Too many breakpoints (> %d) for monitor.", current_monitor->num_breakpoints);
}