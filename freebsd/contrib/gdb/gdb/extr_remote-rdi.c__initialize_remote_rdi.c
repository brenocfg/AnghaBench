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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adp_SetLogEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Adp_SetLogfile (int /*<<< orphan*/ ) ; 
 struct cmd_list_element* add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_setshow_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_rdi_ops ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  filename_completer ; 
 int /*<<< orphan*/  init_rdi_ops () ; 
 int /*<<< orphan*/  log_enable ; 
 int /*<<< orphan*/  log_filename ; 
 int /*<<< orphan*/  maintenancelist ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  rdi_heartbeat ; 
 int /*<<< orphan*/  rdilogenable_command ; 
 int /*<<< orphan*/  rdilogfile_command ; 
 int /*<<< orphan*/  rom_at_zero ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void
_initialize_remote_rdi (void)
{
  struct cmd_list_element *c;

  init_rdi_ops ();
  add_target (&arm_rdi_ops);

  log_filename = xstrdup ("rdi.log");
  Adp_SetLogfile (log_filename);
  Adp_SetLogEnable (log_enable);

  c = add_cmd ("rdilogfile", class_maintenance,
	       rdilogfile_command,
	       "Set filename for ADP packet log.\n"
	       "This file is used to log Angel Debugger Protocol packets.\n"
	       "With a single argument, sets the logfile name to that value.\n"
	       "Without an argument, shows the current logfile name.\n"
	       "See also: rdilogenable\n",
	       &maintenancelist);
  set_cmd_completer (c, filename_completer);

  add_cmd ("rdilogenable", class_maintenance,
	   rdilogenable_command,
	   "Set enable logging of ADP packets.\n"
	   "This will log ADP packets exchanged between gdb and the\n"
	   "rdi target device.\n"
	   "An argument of 1, t, true, y or yes will enable.\n"
	   "An argument of 0, f, false, n or no will disabled.\n"
	   "Withough an argument, it will display current state.\n",
	   &maintenancelist);

  add_setshow_boolean_cmd
    ("rdiromatzero", no_class, &rom_at_zero,
     "Set target has ROM at addr 0.\n"
     "A true value disables vector catching, false enables vector catching.\n"
     "This is evaluated at the time the 'target rdi' command is executed\n",
     "Show if target has ROM at addr 0.\n",
     NULL, NULL,
     &setlist, &showlist);

  add_setshow_boolean_cmd
    ("rdiheartbeat", no_class, &rdi_heartbeat,
     "Set enable for ADP heartbeat packets.\n"
     "I don't know why you would want this. If you enable them,\n"
     "it will confuse ARM and EPI JTAG interface boxes as well\n"
     "as the Angel Monitor.\n",
     "Show enable for ADP heartbeat packets.\n",
     NULL, NULL,
     &setlist, &showlist);
}