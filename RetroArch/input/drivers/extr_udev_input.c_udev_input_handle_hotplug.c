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
struct TYPE_5__ {int /*<<< orphan*/  monitor; } ;
typedef  TYPE_1__ udev_input_t ;
struct udev_device {int dummy; } ;
typedef  enum udev_input_dev_type { ____Placeholder_udev_input_dev_type } udev_input_dev_type ;
typedef  int /*<<< orphan*/  device_handle_cb ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,char const*) ; 
 int UDEV_INPUT_KEYBOARD ; 
 int UDEV_INPUT_MOUSE ; 
 int UDEV_INPUT_TOUCHPAD ; 
 int /*<<< orphan*/ * g_dev_type_str ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 char* udev_device_get_action (struct udev_device*) ; 
 char* udev_device_get_devnode (struct udev_device*) ; 
 char* udev_device_get_property_value (struct udev_device*,char*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 int /*<<< orphan*/  udev_handle_keyboard ; 
 int /*<<< orphan*/  udev_handle_mouse ; 
 int /*<<< orphan*/  udev_input_add_device (TYPE_1__*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_input_remove_device (TYPE_1__*,char const*) ; 
 struct udev_device* udev_monitor_receive_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udev_input_handle_hotplug(udev_input_t *udev)
{
   device_handle_cb cb;
   enum udev_input_dev_type dev_type = UDEV_INPUT_KEYBOARD;
   const char *val_key               = NULL;
   const char *val_mouse             = NULL;
   const char *val_touchpad          = NULL;
   const char *action                = NULL;
   const char *devnode               = NULL;
   struct udev_device *dev           = udev_monitor_receive_device(
         udev->monitor);

   if (!dev)
      return;

   val_key       = udev_device_get_property_value(dev, "ID_INPUT_KEY");
   val_mouse     = udev_device_get_property_value(dev, "ID_INPUT_MOUSE");
   val_touchpad  = udev_device_get_property_value(dev, "ID_INPUT_TOUCHPAD");
   action        = udev_device_get_action(dev);
   devnode       = udev_device_get_devnode(dev);

   if (val_key && string_is_equal(val_key, "1") && devnode)
   {
      /* EV_KEY device, can be a keyboard or a remote control device.  */
      dev_type   = UDEV_INPUT_KEYBOARD;
      cb         = udev_handle_keyboard;
   }
   else if (val_mouse && string_is_equal(val_mouse, "1") && devnode)
   {
      dev_type   = UDEV_INPUT_MOUSE;
      cb         = udev_handle_mouse;
   }
   else if (val_touchpad && string_is_equal(val_touchpad, "1") && devnode)
   {
      dev_type   = UDEV_INPUT_TOUCHPAD;
      cb         = udev_handle_mouse;
   }
   else
      goto end;

   if (string_is_equal(action, "add"))
   {
      RARCH_LOG("[udev]: Hotplug add %s: %s.\n",
            g_dev_type_str[dev_type], devnode);
      udev_input_add_device(udev, dev_type, devnode, cb);
   }
   else if (string_is_equal(action, "remove"))
   {
      RARCH_LOG("[udev]: Hotplug remove %s: %s.\n",
            g_dev_type_str[dev_type], devnode);
      udev_input_remove_device(udev, devnode);
   }

end:
   udev_device_unref(dev);
}