#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ wiiu_attach_event ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  HIDDevice ;
typedef  int /*<<< orphan*/  HIDClient ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_UNUSED ; 
 int /*<<< orphan*/  DEVICE_USED ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  delete_attach_event (TYPE_1__*) ; 
 int /*<<< orphan*/  log_device (int /*<<< orphan*/ *) ; 
 TYPE_1__* new_attach_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronized_add_event (TYPE_1__*) ; 

__attribute__((used)) static int32_t wiiu_attach_callback(HIDClient *client,
      HIDDevice *device, uint32_t attach)
{
   wiiu_attach_event *event = NULL;

   if (attach)
   {
      RARCH_LOG("[hid]: Device attach event generated.\n");
      log_device(device);
   }
   else
   {
      RARCH_LOG("[hid]: Device detach event generated.\n");
   }

   if (device)
      event = new_attach_event(device);

   if (!event)
      goto error;

   event->type = attach;
   synchronized_add_event(event);

   return DEVICE_USED;

error:
   delete_attach_event(event);
   return DEVICE_UNUSED;
}