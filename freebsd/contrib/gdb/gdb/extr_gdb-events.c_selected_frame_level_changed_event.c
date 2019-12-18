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
struct TYPE_2__ {int /*<<< orphan*/  (* selected_frame_level_changed ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* current_event_hooks ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gdb_events_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  stub1 (int) ; 

void
selected_frame_level_changed_event (int level)
{
  if (gdb_events_debug)
    fprintf_unfiltered (gdb_stdlog, "selected_frame_level_changed_event\n");
  if (!current_event_hooks->selected_frame_level_changed)
    return;
  current_event_hooks->selected_frame_level_changed (level);
}