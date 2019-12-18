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
struct nouveau_event {int index_nr; int /*<<< orphan*/  (* disable ) (struct nouveau_event*,int) ;TYPE_1__* index; } ;
struct TYPE_2__ {scalar_t__ refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nouveau_event*,int) ; 

void
nouveau_event_disable_locked(struct nouveau_event *event, int index, int refs)
{
	if (index >= event->index_nr)
		return;

	event->index[index].refs -= refs;
	if (!event->index[index].refs && event->disable)
		event->disable(event, index);
}