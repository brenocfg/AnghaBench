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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
struct TYPE_2__ {int flags; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MO_HAS_BLOCKWRITES ; 
 TYPE_1__* current_monitor ; 
 int monitor_read_memory (int /*<<< orphan*/ ,char*,int) ; 
 int monitor_write_memory (int /*<<< orphan*/ ,char*,int) ; 
 int monitor_write_memory_block (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
monitor_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		     struct mem_attrib *attrib, struct target_ops *target)
{
  int res;

  if (write)
    {
      if (current_monitor->flags & MO_HAS_BLOCKWRITES)
	res = monitor_write_memory_block(memaddr, myaddr, len);
      else
	res = monitor_write_memory(memaddr, myaddr, len);
    }
  else
    {
      res = monitor_read_memory(memaddr, myaddr, len);
    }

  return res;
}