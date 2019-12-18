#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  polling_thread_quit; } ;
typedef  TYPE_1__ wiiu_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  synchronized_get_events_list () ; 
 int /*<<< orphan*/  wiiu_handle_attach_events (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiu_poll_adapters (TYPE_1__*) ; 

__attribute__((used)) static int wiiu_hid_polling_thread(int argc, const char **argv)
{
   wiiu_hid_t *hid = (wiiu_hid_t *)argv;

   RARCH_LOG("[hid]: polling thread is starting\n");

   while(!hid->polling_thread_quit)
   {
      wiiu_handle_attach_events(hid, synchronized_get_events_list());
      wiiu_poll_adapters(hid);
   }

   RARCH_LOG("[hid]: polling thread is stopping\n");
   return 0;
}