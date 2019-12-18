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
struct timeval {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  quit; } ;
typedef  TYPE_1__ libusb_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  libusb_handle_events_timeout_completed (int /*<<< orphan*/ *,struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poll_thread(void *data)
{
   libusb_hid_t *hid = (libusb_hid_t*)data;

   while (!hid->quit)
   {
      struct timeval timeout = {0};
      libusb_handle_events_timeout_completed(NULL,
            &timeout, &hid->quit);
   }
}