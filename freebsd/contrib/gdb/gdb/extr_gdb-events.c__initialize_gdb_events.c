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
struct cmd_list_element {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  selected_thread_changed; int /*<<< orphan*/  selected_frame_level_changed; int /*<<< orphan*/  target_changed; int /*<<< orphan*/  architecture_changed; int /*<<< orphan*/  tracepoint_modify; int /*<<< orphan*/  tracepoint_delete; int /*<<< orphan*/  tracepoint_create; int /*<<< orphan*/  breakpoint_modify; int /*<<< orphan*/  breakpoint_delete; int /*<<< orphan*/  breakpoint_create; } ;

/* Variables and functions */
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  deprecate_cmd (struct cmd_list_element*,char*) ; 
 int /*<<< orphan*/  gdb_events_debug ; 
 int /*<<< orphan*/  queue_architecture_changed ; 
 int /*<<< orphan*/  queue_breakpoint_create ; 
 int /*<<< orphan*/  queue_breakpoint_delete ; 
 int /*<<< orphan*/  queue_breakpoint_modify ; 
 TYPE_1__ queue_event_hooks ; 
 int /*<<< orphan*/  queue_selected_frame_level_changed ; 
 int /*<<< orphan*/  queue_selected_thread_changed ; 
 int /*<<< orphan*/  queue_target_changed ; 
 int /*<<< orphan*/  queue_tracepoint_create ; 
 int /*<<< orphan*/  queue_tracepoint_delete ; 
 int /*<<< orphan*/  queue_tracepoint_modify ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_gdb_events (void)
{
  struct cmd_list_element *c;
#if WITH_GDB_EVENTS
  queue_event_hooks.breakpoint_create = queue_breakpoint_create;
  queue_event_hooks.breakpoint_delete = queue_breakpoint_delete;
  queue_event_hooks.breakpoint_modify = queue_breakpoint_modify;
  queue_event_hooks.tracepoint_create = queue_tracepoint_create;
  queue_event_hooks.tracepoint_delete = queue_tracepoint_delete;
  queue_event_hooks.tracepoint_modify = queue_tracepoint_modify;
  queue_event_hooks.architecture_changed = queue_architecture_changed;
  queue_event_hooks.target_changed = queue_target_changed;
  queue_event_hooks.selected_frame_level_changed = queue_selected_frame_level_changed;
  queue_event_hooks.selected_thread_changed = queue_selected_thread_changed;
#endif

  c = add_set_cmd ("eventdebug", class_maintenance, var_zinteger,
		   (char *) (&gdb_events_debug), "Set event debugging.\n\
When non-zero, event/notify debugging is enabled.", &setlist);
  deprecate_cmd (c, "set debug event");
  deprecate_cmd (add_show_from_set (c, &showlist), "show debug event");

  add_show_from_set (add_set_cmd ("event",
				  class_maintenance,
				  var_zinteger,
				  (char *) (&gdb_events_debug),
				  "Set event debugging.\n\
When non-zero, event/notify debugging is enabled.", &setdebuglist),
		     &showdebuglist);
}