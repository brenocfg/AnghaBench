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
struct serio {int /*<<< orphan*/  dev; struct serio* parent; struct serio* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_destroy_port (struct serio*) ; 

__attribute__((used)) static void serio_disconnect_port(struct serio *serio)
{
	struct serio *s, *parent;

	if (serio->child) {
		/*
		 * Children ports should be disconnected and destroyed
		 * first, staring with the leaf one, since we don't want
		 * to do recursion
		 */
		for (s = serio; s->child; s = s->child)
			/* empty */;

		do {
			parent = s->parent;

			device_release_driver(&s->dev);
			serio_destroy_port(s);
		} while ((s = parent) != serio);
	}

	/*
	 * Ok, no children left, now disconnect this port
	 */
	device_release_driver(&serio->dev);
}