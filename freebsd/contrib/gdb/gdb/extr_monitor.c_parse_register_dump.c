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
struct re_registers {int* end; int* start; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* supply_register ) (char*,int,char*,int) ;} ;

/* Variables and functions */
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  memset (struct re_registers*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int re_search (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,struct re_registers*) ; 
 int /*<<< orphan*/  register_pattern ; 
 int /*<<< orphan*/  stub1 (char*,int,char*,int) ; 

__attribute__((used)) static void
parse_register_dump (char *buf, int len)
{
  monitor_debug ("MON Parsing  register dump\n");
  while (1)
    {
      int regnamelen, vallen;
      char *regname, *val;
      /* Element 0 points to start of register name, and element 1
         points to the start of the register value.  */
      struct re_registers register_strings;

      memset (&register_strings, 0, sizeof (struct re_registers));

      if (re_search (&register_pattern, buf, len, 0, len,
		     &register_strings) == -1)
	break;

      regnamelen = register_strings.end[1] - register_strings.start[1];
      regname = buf + register_strings.start[1];
      vallen = register_strings.end[2] - register_strings.start[2];
      val = buf + register_strings.start[2];

      current_monitor->supply_register (regname, regnamelen, val, vallen);

      buf += register_strings.end[0];
      len -= register_strings.end[0];
    }
}