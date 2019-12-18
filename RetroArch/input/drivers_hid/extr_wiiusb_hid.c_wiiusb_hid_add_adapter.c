#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  connections; struct wiiusb_adapter* adapters_head; } ;
typedef  TYPE_1__ wiiusb_hid_t ;
struct TYPE_15__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; } ;
typedef  TYPE_2__ usb_device_entry ;
struct TYPE_16__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
typedef  TYPE_3__ usb_devdesc ;
struct wiiusb_adapter {scalar_t__ endpoint_in; int slot; int /*<<< orphan*/  handle; struct wiiusb_adapter* send_control_buffer; int /*<<< orphan*/  device_id; struct wiiusb_adapter* next; TYPE_1__* hid; void* data; int /*<<< orphan*/  send_control_type; } ;
typedef  int int32_t ;
struct TYPE_17__ {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  USB_CloseDevice (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DeviceRemovalNotifyAsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wiiusb_adapter*) ; 
 int /*<<< orphan*/  USB_FreeDescriptors (TYPE_3__*) ; 
 int /*<<< orphan*/  USB_GetDescriptors (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ USB_OpenDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIIUSB_SC_NONE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct wiiusb_adapter*) ; 
 scalar_t__ isRetrodeGamepad (TYPE_3__) ; 
 scalar_t__ isRetrodeMouse (TYPE_3__) ; 
 void* memalign (int,int) ; 
 int /*<<< orphan*/  pad_connection_has_interface (int /*<<< orphan*/ ,int) ; 
 void* pad_connection_pad_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wiiusb_adapter*,TYPE_6__*) ; 
 int /*<<< orphan*/  wiiusb_get_description (TYPE_2__*,struct wiiusb_adapter*,TYPE_3__*) ; 
 TYPE_6__ wiiusb_hid ; 
 int /*<<< orphan*/  wiiusb_hid_device_add_autodetect (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* wiiusb_hid_joypad_name (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wiiusb_hid_removal_cb ; 

__attribute__((used)) static int wiiusb_hid_add_adapter(void *data, usb_device_entry *dev)
{
   usb_devdesc desc;
   const char        *device_name = NULL;
   wiiusb_hid_t              *hid = (wiiusb_hid_t*)data;
   struct wiiusb_adapter *adapter = (struct wiiusb_adapter*)
      calloc(1, sizeof(struct wiiusb_adapter));
   int i;
   int32_t slot1;

   if (!adapter)
      return -1;

   if (!hid)
   {
      free(adapter);
      RARCH_ERR("Allocation of adapter failed.\n");
      return -1;
   }

   if (USB_OpenDevice(dev->device_id, dev->vid, dev->pid, &adapter->handle) < 0)
   {
      RARCH_ERR("Error opening device 0x%p (VID/PID: %04x:%04x).\n",
           dev->device_id, dev->vid, dev->pid);
      free(adapter);
      return -1;
   }

   adapter->device_id = dev->device_id;

   USB_GetDescriptors(adapter->handle, &desc);

   if (isRetrodeMouse(desc))
   {
       RARCH_LOG("Retrode SNES mouse found (currently not supported)\n");
       goto error;
   }

   wiiusb_get_description(dev, adapter, &desc);

   if (adapter->endpoint_in == 0)
   {
      RARCH_ERR("Could not find HID config for device.\n");
      goto error;
   }

   /* Allocate mem for the send control buffer, 32bit aligned */
   adapter->send_control_type   = WIIUSB_SC_NONE;
   adapter->send_control_buffer = memalign(32, 128);

   if (!adapter->send_control_buffer)
   {
      RARCH_ERR("Error creating send control buffer.\n");
      goto error;
   }

   /* Sent the pad name as dummy, we don't know the
    * control name until we get its interface */
   adapter->slot = pad_connection_pad_init(hid->connections,
         "hid", desc.idVendor, desc.idProduct,
         adapter, &wiiusb_hid);

   if (adapter->slot == -1)
      goto error;

   if (!pad_connection_has_interface(hid->connections, adapter->slot))
   {
      RARCH_ERR(" Interface not found.\n");
      goto error;
   }

   adapter->data      = memalign(32, 128);
   adapter->hid       = hid;
   adapter->next      = hid->adapters_head;
   hid->adapters_head = adapter;

   /*  Get the name from the interface */
   device_name = wiiusb_hid_joypad_name(hid, adapter->slot);

   RARCH_LOG("Interface found: [%s].\n", device_name);

   RARCH_LOG("Device 0x%p attached (VID/PID: %04x:%04x).\n",
         adapter->device_id, desc.idVendor, desc.idProduct);

   if (isRetrodeGamepad(desc))
   {
       /* Retrode port #1 */
       RARCH_LOG("Interface Retrode1 gamepad slot: %d\n", adapter->slot);
       wiiusb_hid_device_add_autodetect(adapter->slot, device_name, wiiusb_hid.ident, desc.idVendor, desc.idProduct);
       /* Retrode port #2, #3, #4 */
       for (i = 2; i <= 4; i++)
       {
           slot1 = pad_connection_pad_init(hid->connections, "hid", desc.idVendor, desc.idProduct, adapter, &wiiusb_hid);
           if (slot1 == -1)
               RARCH_LOG("No slot free for Retrode%d gamepad\n", i);
           else
           {
               RARCH_LOG("Interface Retrode%d gamepad slot: %d\n", i, slot1);
               wiiusb_hid_device_add_autodetect(slot1, device_name, wiiusb_hid.ident, desc.idVendor, desc.idProduct);
           }
       }
   }
   else
       wiiusb_hid_device_add_autodetect(adapter->slot,
             device_name, wiiusb_hid.ident, desc.idVendor, desc.idProduct);

   USB_FreeDescriptors(&desc);
   USB_DeviceRemovalNotifyAsync(adapter->handle, wiiusb_hid_removal_cb, adapter);

   return 0;

error:
   if (adapter->send_control_buffer)
      free(adapter->send_control_buffer);
   if (adapter)
      free(adapter);
   USB_FreeDescriptors(&desc);
   USB_CloseDevice(&adapter->handle);
   return -1;
}