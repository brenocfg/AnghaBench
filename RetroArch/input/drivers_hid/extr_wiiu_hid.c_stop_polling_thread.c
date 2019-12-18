#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int polling_thread_quit; int /*<<< orphan*/ * polling_thread_stack; int /*<<< orphan*/ * polling_thread; int /*<<< orphan*/ * client; } ;
typedef  TYPE_1__ wiiu_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIDDelClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSJoinThread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stop_polling_thread(wiiu_hid_t *hid)
{
   int thread_result = 0;
   RARCH_LOG("[hid]: stopping polling thread.\n");

   if (!hid || !hid->polling_thread)
      return;

   /* Unregister our HID client so we don't get any new events. */
   if (hid->client)
   {
     HIDDelClient(hid->client);
     hid->client = NULL;
   }

   /* tell the thread it's time to stop. */
   hid->polling_thread_quit = true;
   /* This returns once the thread runs and the cleanup method completes. */
   OSJoinThread(hid->polling_thread, &thread_result);
   free(hid->polling_thread);
   free(hid->polling_thread_stack);
   hid->polling_thread = NULL;
   hid->polling_thread_stack = NULL;
}