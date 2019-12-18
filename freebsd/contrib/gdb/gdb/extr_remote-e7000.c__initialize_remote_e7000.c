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

/* Variables and functions */
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  e7000_command ; 
 int /*<<< orphan*/  e7000_drain_command ; 
 int /*<<< orphan*/  e7000_ftp_command ; 
 int /*<<< orphan*/  e7000_login_command ; 
 int /*<<< orphan*/  e7000_ops ; 
 int /*<<< orphan*/  init_e7000_ops () ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  use_hard_breakpoints ; 
 int /*<<< orphan*/  var_integer ; 

void
_initialize_remote_e7000 (void)
{
  init_e7000_ops ();
  add_target (&e7000_ops);

  add_com ("e7000", class_obscure, e7000_command,
	   "Send a command to the e7000 monitor.");

  add_com ("ftplogin", class_obscure, e7000_login_command,
	   "Login to machine and change to directory.");

  add_com ("ftpload", class_obscure, e7000_ftp_command,
	   "Fetch and load a file from previously described place.");

  add_com ("drain", class_obscure, e7000_drain_command,
	   "Drain pending e7000 text buffers.");

  add_show_from_set (add_set_cmd ("usehardbreakpoints", no_class,
				var_integer, (char *) &use_hard_breakpoints,
	"Set use of hardware breakpoints for all breakpoints.\n", &setlist),
		     &showlist);
}