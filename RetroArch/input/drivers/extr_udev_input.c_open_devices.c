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
struct TYPE_4__ {int /*<<< orphan*/  udev; } ;
typedef  TYPE_1__ udev_input_t ;
struct udev_list_entry {int dummy; } ;
struct udev_enumerate {int dummy; } ;
struct udev_device {int dummy; } ;
typedef  enum udev_input_dev_type { ____Placeholder_udev_input_dev_type } udev_input_dev_type ;
typedef  int /*<<< orphan*/  device_handle_cb ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*,int /*<<< orphan*/ ,char const*) ; 
 int UDEV_INPUT_KEYBOARD ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 char** g_dev_type_str ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* udev_device_get_devnode (struct udev_device*) ; 
 struct udev_device* udev_device_new_from_syspath (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  udev_device_unref (struct udev_device*) ; 
 int /*<<< orphan*/  udev_enumerate_add_match_property (struct udev_enumerate*,char const*,char*) ; 
 struct udev_list_entry* udev_enumerate_get_list_entry (struct udev_enumerate*) ; 
 struct udev_enumerate* udev_enumerate_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_enumerate_scan_devices (struct udev_enumerate*) ; 
 int /*<<< orphan*/  udev_enumerate_unref (struct udev_enumerate*) ; 
 int /*<<< orphan*/  udev_input_add_device (TYPE_1__*,int,char const*,int /*<<< orphan*/ ) ; 
 char* udev_list_entry_get_name (struct udev_list_entry*) ; 
 struct udev_list_entry* udev_list_entry_get_next (struct udev_list_entry*) ; 

__attribute__((used)) static bool open_devices(udev_input_t *udev,
      enum udev_input_dev_type type, device_handle_cb cb)
{
   const char             *type_str = g_dev_type_str[type];
   struct udev_list_entry     *devs = NULL;
   struct udev_list_entry     *item = NULL;
   struct udev_enumerate *enumerate = udev_enumerate_new(udev->udev);
   int device_index                 = 0;

   if (!enumerate)
      return false;

   udev_enumerate_add_match_property(enumerate, type_str, "1");
   udev_enumerate_scan_devices(enumerate);
   devs = udev_enumerate_get_list_entry(enumerate);

   for (item = devs; item; item = udev_list_entry_get_next(item))
   {
      const char *name        = udev_list_entry_get_name(item);

      /* Get the filename of the /sys entry for the device
       * and create a udev_device object (dev) representing it. */
      struct udev_device *dev = udev_device_new_from_syspath(udev->udev, name);
      const char *devnode     = udev_device_get_devnode(dev);

      if (devnode)
      {
         int fd = open(devnode, O_RDONLY | O_NONBLOCK);

         if (fd != -1)
         {
            if (!udev_input_add_device(udev, type, devnode, cb))
               RARCH_ERR("[udev] Failed to open device: %s (%s).\n",
                     devnode, strerror(errno));
            else
               RARCH_LOG("[udev]: %s #%d (%s).\n",
                     type == UDEV_INPUT_KEYBOARD ? "Keyboard" : "Mouse",
                     device_index++, devnode);
            close(fd);
         }
      }

      udev_device_unref(dev);
   }

   udev_enumerate_unref(enumerate);
   return true;
}