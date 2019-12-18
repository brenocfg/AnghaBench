#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cmdll; } ;
struct TYPE_4__ {TYPE_1__ setmem; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 TYPE_2__* current_monitor ; 
 int monitor_write_memory_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int monitor_write_memory_longlongs (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
monitor_write_memory_block (CORE_ADDR memaddr, char *myaddr, int len)
{
  int written;
  written = 0;
  /* FIXME: This would be a good place to put the zero test */
#if 1
  if ((len > 8) && (((len & 0x07)) == 0) && current_monitor->setmem.cmdll)
    {
      return monitor_write_memory_longlongs (memaddr, myaddr, len);
    }
#endif
  written = monitor_write_memory_bytes (memaddr, myaddr, len);
  return written;
}