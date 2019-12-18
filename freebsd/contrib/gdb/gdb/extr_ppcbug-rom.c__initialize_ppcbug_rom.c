#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_target (TYPE_1__*) ; 
 int /*<<< orphan*/  init_monitor_ops (TYPE_1__*) ; 
 int /*<<< orphan*/  init_ppc_cmds (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ppcbug_cmds0 ; 
 int /*<<< orphan*/  ppcbug_cmds1 ; 
 int /*<<< orphan*/  ppcbug_open0 ; 
 int /*<<< orphan*/  ppcbug_open1 ; 
 TYPE_1__ ppcbug_ops0 ; 
 TYPE_1__ ppcbug_ops1 ; 

void
_initialize_ppcbug_rom (void)
{
  init_ppc_cmds ("lo 0\r", &ppcbug_cmds0, &ppcbug_ops0);
  init_ppc_cmds ("lo 1\r", &ppcbug_cmds1, &ppcbug_ops1);
  init_monitor_ops (&ppcbug_ops0);

  ppcbug_ops0.to_shortname = "ppcbug";
  ppcbug_ops0.to_longname = "PowerPC PPCBug monitor on port 0";
  ppcbug_ops0.to_doc = "Debug via the PowerPC PPCBug monitor using port 0.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  ppcbug_ops0.to_open = ppcbug_open0;

  add_target (&ppcbug_ops0);

  init_monitor_ops (&ppcbug_ops1);

  ppcbug_ops1.to_shortname = "ppcbug1";
  ppcbug_ops1.to_longname = "PowerPC PPCBug monitor on port 1";
  ppcbug_ops1.to_doc = "Debug via the PowerPC PPCBug monitor using port 1.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  ppcbug_ops1.to_open = ppcbug_open1;

  add_target (&ppcbug_ops1);
}