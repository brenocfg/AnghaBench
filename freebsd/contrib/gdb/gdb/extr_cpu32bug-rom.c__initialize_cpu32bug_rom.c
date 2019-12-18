#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_target (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu32bug_open ; 
 TYPE_1__ cpu32bug_ops ; 
 int /*<<< orphan*/  init_cpu32bug_cmds () ; 
 int /*<<< orphan*/  init_monitor_ops (TYPE_1__*) ; 

void
_initialize_cpu32bug_rom (void)
{
  init_cpu32bug_cmds ();
  init_monitor_ops (&cpu32bug_ops);

  cpu32bug_ops.to_shortname = "cpu32bug";
  cpu32bug_ops.to_longname = "CPU32Bug monitor";
  cpu32bug_ops.to_doc = "Debug via the CPU32Bug monitor.\n\
Specify the serial device it is connected to (e.g. /dev/ttya).";
  cpu32bug_ops.to_open = cpu32bug_open;

  add_target (&cpu32bug_ops);
}