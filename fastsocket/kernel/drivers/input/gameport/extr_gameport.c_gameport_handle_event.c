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
struct gameport_event {int type; int /*<<< orphan*/  object; } ;

/* Variables and functions */
#define  GAMEPORT_ATTACH_DRIVER 129 
#define  GAMEPORT_REGISTER_PORT 128 
 int /*<<< orphan*/  gameport_add_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_attach_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_free_event (struct gameport_event*) ; 
 struct gameport_event* gameport_get_event () ; 
 int /*<<< orphan*/  gameport_mutex ; 
 int /*<<< orphan*/  gameport_remove_duplicate_events (struct gameport_event*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gameport_handle_event(void)
{
	struct gameport_event *event;

	mutex_lock(&gameport_mutex);

	/*
	 * Note that we handle only one event here to give swsusp
	 * a chance to freeze kgameportd thread. Gameport events
	 * should be pretty rare so we are not concerned about
	 * taking performance hit.
	 */
	if ((event = gameport_get_event())) {

		switch (event->type) {
			case GAMEPORT_REGISTER_PORT:
				gameport_add_port(event->object);
				break;

			case GAMEPORT_ATTACH_DRIVER:
				gameport_attach_driver(event->object);
				break;

			default:
				break;
		}

		gameport_remove_duplicate_events(event);
		gameport_free_event(event);
	}

	mutex_unlock(&gameport_mutex);
}