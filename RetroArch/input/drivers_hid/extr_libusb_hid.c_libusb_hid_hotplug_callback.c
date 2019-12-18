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
struct libusb_device {int dummy; } ;
struct libusb_context {int dummy; } ;
typedef  int libusb_hotplug_event ;
typedef  int /*<<< orphan*/  libusb_hid_t ;

/* Variables and functions */
#define  LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED 129 
#define  LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT 128 
 int /*<<< orphan*/  RARCH_WARN (char*,int) ; 
 int /*<<< orphan*/  add_adapter (int /*<<< orphan*/ *,struct libusb_device*) ; 
 int /*<<< orphan*/  remove_adapter (int /*<<< orphan*/ *,struct libusb_device*) ; 

__attribute__((used)) static int libusb_hid_hotplug_callback(struct libusb_context *ctx,
      struct libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
   libusb_hid_t *hid = (libusb_hid_t*)user_data;

   switch (event)
   {
      case LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED:
         add_adapter(hid, dev);
         break;
      case LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT:
         remove_adapter(hid, dev);
         break;
      default:
         RARCH_WARN("Unhandled event: %d\n", event);
         break;
   }

   return 0;
}