#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct serio {int registered; TYPE_3__ dev; int /*<<< orphan*/  node; TYPE_1__* parent; int /*<<< orphan*/  (* stop ) (struct serio*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * child; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (TYPE_3__*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  serio_continue_rx (TYPE_1__*) ; 
 struct serio* serio_get_pending_child (struct serio*) ; 
 int /*<<< orphan*/  serio_id_attr_group ; 
 int /*<<< orphan*/  serio_pause_rx (TYPE_1__*) ; 
 int /*<<< orphan*/  serio_remove_pending_events (struct serio*) ; 
 int /*<<< orphan*/  stub1 (struct serio*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serio_destroy_port(struct serio *serio)
{
	struct serio *child;

	child = serio_get_pending_child(serio);
	if (child) {
		serio_remove_pending_events(child);
		put_device(&child->dev);
	}

	if (serio->stop)
		serio->stop(serio);

	if (serio->parent) {
		serio_pause_rx(serio->parent);
		serio->parent->child = NULL;
		serio_continue_rx(serio->parent);
		serio->parent = NULL;
	}

	if (serio->registered) {
		sysfs_remove_group(&serio->dev.kobj, &serio_id_attr_group);
		device_del(&serio->dev);
		serio->registered = false;
	}

	list_del_init(&serio->node);
	serio_remove_pending_events(serio);
	put_device(&serio->dev);
}