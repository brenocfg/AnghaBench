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
struct event {struct event* next; } ;

/* Variables and functions */
 struct event* pending_events ; 

__attribute__((used)) static void
append (struct event *new_event)
{
  struct event **event = &pending_events;
  while ((*event) != NULL)
    event = &((*event)->next);
  (*event) = new_event;
  (*event)->next = NULL;
}