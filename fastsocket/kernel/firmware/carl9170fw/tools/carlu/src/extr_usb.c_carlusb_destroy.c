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
struct carlu {int stop_event_polling; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  event_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  carlusb_cancel_rings (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_free_rings (struct carlu*) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void carlusb_destroy(struct carlu *ar)
{
	int event_thread_status;

	dbg("==>release device.\n");

	ar->stop_event_polling = true;

	carlusb_cancel_rings(ar);

	SDL_WaitThread(ar->event_thread, &event_thread_status);

	carlusb_free_rings(ar);
	list_del(&ar->dev_list);
}