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
struct carlu {int /*<<< orphan*/  ctx; int /*<<< orphan*/  stop_event_polling; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  libusb_handle_events (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carlusb_event_thread(void *_ar)
{
	struct carlu *ar = (void *)_ar;
	dbg("event thread active and polling.\n");

	while (!ar->stop_event_polling)
		libusb_handle_events(ar->ctx);

	dbg("==> event thread desixed.\n");
	return 0;
}