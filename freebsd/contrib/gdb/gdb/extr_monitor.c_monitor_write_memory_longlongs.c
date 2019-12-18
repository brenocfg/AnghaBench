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
struct TYPE_5__ {int /*<<< orphan*/  term_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmdll; } ;
struct TYPE_6__ {TYPE_2__ getreg; TYPE_1__ setmem; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 TYPE_3__* current_monitor ; 
 char* longlong_hexchars (long long,char*) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*,...) ; 

__attribute__((used)) static int
monitor_write_memory_longlongs (CORE_ADDR memaddr, char *myaddr, int len)
{
  static char hexstage[20];	/* At least 16 digits required, plus null */
  char *endstring;
  long long *llptr;
  long long value;
  int written = 0;
  llptr = (unsigned long long *) myaddr;
  if (len == 0)
    return 0;
  monitor_printf (current_monitor->setmem.cmdll, memaddr);
  monitor_expect_prompt (NULL, 0);
  while (len >= 8)
    {
      value = *llptr;
      endstring = longlong_hexchars (*llptr, hexstage);
      *endstring = '\0';	/* NUll terminate for printf */
      monitor_printf ("%s\r", hexstage);
      llptr++;
      memaddr += 8;
      written += 8;
      /* If we wanted to, here we could validate the address */
      monitor_expect_prompt (NULL, 0);
      len -= 8;
    }
  /* Now exit the sub mode */
  monitor_printf (current_monitor->getreg.term_cmd);
  monitor_expect_prompt (NULL, 0);
  return written;
}