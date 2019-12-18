#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int quit; int /*<<< orphan*/  ctx; int /*<<< orphan*/  hp; scalar_t__ can_hotplug; scalar_t__ slots; scalar_t__ poll_thread; } ;
typedef  TYPE_2__ libusb_hid_t ;
struct TYPE_8__ {TYPE_1__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ adapters ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  libusb_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_hotplug_deregister_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_connection_destroy (scalar_t__) ; 
 int remove_adapter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (scalar_t__) ; 

__attribute__((used)) static void libusb_hid_free(const void *data)
{
   libusb_hid_t *hid = (libusb_hid_t*)data;

   while(adapters.next)
      if (remove_adapter(hid, adapters.next->device) == -1)
         RARCH_ERR("could not remove device %p\n",
               adapters.next->device);

   if (hid->poll_thread)
   {
      hid->quit = 1;
      sthread_join(hid->poll_thread);
   }

   if (hid->slots)
      pad_connection_destroy(hid->slots);

   if (hid->can_hotplug)
      libusb_hotplug_deregister_callback(hid->ctx, hid->hp);

   libusb_exit(hid->ctx);
   free(hid);
}