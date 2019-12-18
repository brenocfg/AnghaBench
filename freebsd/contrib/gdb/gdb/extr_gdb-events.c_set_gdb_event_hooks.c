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
struct gdb_events {int dummy; } ;

/* Variables and functions */
 struct gdb_events* current_event_hooks ; 
 struct gdb_events queue_event_hooks ; 

struct gdb_events *
set_gdb_event_hooks (struct gdb_events *vector)
{
  struct gdb_events *old_events = current_event_hooks;
  if (vector == NULL)
    current_event_hooks = &queue_event_hooks;
  else
    current_event_hooks = vector;
  return old_events;
}