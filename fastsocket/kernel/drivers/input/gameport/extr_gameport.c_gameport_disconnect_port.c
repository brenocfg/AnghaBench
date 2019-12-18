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
struct gameport {int /*<<< orphan*/  dev; struct gameport* parent; struct gameport* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gameport_destroy_port (struct gameport*) ; 

__attribute__((used)) static void gameport_disconnect_port(struct gameport *gameport)
{
	struct gameport *s, *parent;

	if (gameport->child) {
		/*
		 * Children ports should be disconnected and destroyed
		 * first, staring with the leaf one, since we don't want
		 * to do recursion
		 */
		for (s = gameport; s->child; s = s->child)
			/* empty */;

		do {
			parent = s->parent;

			device_release_driver(&s->dev);
			gameport_destroy_port(s);
		} while ((s = parent) != gameport);
	}

	/*
	 * Ok, no children left, now disconnect this port
	 */
	device_release_driver(&gameport->dev);
}