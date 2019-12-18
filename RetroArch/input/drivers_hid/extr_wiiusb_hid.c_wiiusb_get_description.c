#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* endpoints; scalar_t__ bNumEndpoints; } ;
typedef  TYPE_1__ usb_interfacedesc ;
struct TYPE_7__ {int bmAttributes; int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
typedef  TYPE_2__ usb_endpointdesc ;
typedef  int /*<<< orphan*/  usb_device_entry ;
struct TYPE_8__ {unsigned char bNumConfigurations; TYPE_4__* configurations; } ;
typedef  TYPE_3__ usb_devdesc ;
struct TYPE_9__ {TYPE_1__* interfaces; scalar_t__ bNumInterfaces; } ;
typedef  TYPE_4__ usb_configurationdesc ;
struct wiiusb_adapter {int endpoint_in; int endpoint_out; int /*<<< orphan*/  endpoint_out_max_size; int /*<<< orphan*/  endpoint_in_max_size; } ;

/* Variables and functions */
 int USB_ENDPOINT_IN ; 
 int USB_ENDPOINT_INTERRUPT ; 
 int USB_ENDPOINT_OUT ; 

__attribute__((used)) static void wiiusb_get_description(usb_device_entry *device,
      struct wiiusb_adapter *adapter, usb_devdesc *devdesc)
{
   unsigned char c;
   unsigned i, k;

   for (c = 0; c < devdesc->bNumConfigurations; c++)
   {
      const usb_configurationdesc *config = &devdesc->configurations[c];

      for (i = 0; i < (int)config->bNumInterfaces; i++)
      {
         const usb_interfacedesc *inter = &config->interfaces[i];

         for (k = 0; k < (int)inter->bNumEndpoints; k++)
         {
            const usb_endpointdesc *epdesc = &inter->endpoints[k];
            bool is_int = (epdesc->bmAttributes & 0x03)     == USB_ENDPOINT_INTERRUPT;
            bool is_out = (epdesc->bEndpointAddress & 0x80) == USB_ENDPOINT_OUT;
            bool is_in  = (epdesc->bEndpointAddress & 0x80) == USB_ENDPOINT_IN;

            if (is_int)
            {
               if (is_in)
               {
                  adapter->endpoint_in = epdesc->bEndpointAddress;
                  adapter->endpoint_in_max_size = epdesc->wMaxPacketSize;
               }
               if (is_out)
               {
                  adapter->endpoint_out = epdesc->bEndpointAddress;
                  adapter->endpoint_out_max_size = epdesc->wMaxPacketSize;
               }
            }
         }
         break;
      }
   }
}