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
struct nouveau_event {int index_nr; TYPE_1__* index; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nouveau_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nouveau_event_create(int index_nr, struct nouveau_event **pevent)
{
	struct nouveau_event *event;
	int i;

	event = *pevent = kzalloc(sizeof(*event) + index_nr *
				  sizeof(event->index[0]), GFP_KERNEL);
	if (!event)
		return -ENOMEM;

	spin_lock_init(&event->lock);
	for (i = 0; i < index_nr; i++)
		INIT_LIST_HEAD(&event->index[i].list);
	event->index_nr = index_nr;
	return 0;
}