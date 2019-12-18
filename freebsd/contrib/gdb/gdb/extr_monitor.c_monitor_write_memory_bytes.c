#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  term_cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmdb; } ;
struct TYPE_6__ {TYPE_1__ getreg; TYPE_2__ setmem; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 TYPE_3__* current_monitor ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*,...) ; 

__attribute__((used)) static int
monitor_write_memory_bytes (CORE_ADDR memaddr, char *myaddr, int len)
{
  unsigned char val;
  int written = 0;
  if (len == 0)
    return 0;
  /* Enter the sub mode */
  monitor_printf (current_monitor->setmem.cmdb, memaddr);
  monitor_expect_prompt (NULL, 0);
  while (len)
    {
      val = *myaddr;
      monitor_printf ("%x\r", val);
      myaddr++;
      memaddr++;
      written++;
      /* If we wanted to, here we could validate the address */
      monitor_expect_prompt (NULL, 0);
      len--;
    }
  /* Now exit the sub mode */
  monitor_printf (current_monitor->getreg.term_cmd);
  monitor_expect_prompt (NULL, 0);
  return written;
}