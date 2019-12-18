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
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmark ; 
 int /*<<< orphan*/  init_base_monitor_ops () ; 
 int /*<<< orphan*/  monitor_debug_p ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_remote_monitors (void)
{
  init_base_monitor_ops ();
  add_show_from_set (add_set_cmd ("hash", no_class, var_boolean,
				  (char *) &hashmark,
				  "Set display of activity while downloading a file.\n\
When enabled, a hashmark \'#\' is displayed.",
				  &setlist),
		     &showlist);

  add_show_from_set
    (add_set_cmd ("monitor", no_class, var_zinteger,
		  (char *) &monitor_debug_p,
		  "Set debugging of remote monitor communication.\n\
When enabled, communication between GDB and the remote monitor\n\
is displayed.", &setdebuglist),
     &showdebuglist);
}