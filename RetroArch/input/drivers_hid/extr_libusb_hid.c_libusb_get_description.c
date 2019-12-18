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
struct libusb_interface_descriptor {scalar_t__ bInterfaceClass; struct libusb_endpoint_descriptor* endpoint; scalar_t__ bNumEndpoints; scalar_t__ bInterfaceNumber; } ;
struct libusb_interface {int num_altsetting; struct libusb_interface_descriptor* altsetting; } ;
struct libusb_endpoint_descriptor {int bmAttributes; int bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct libusb_device {int dummy; } ;
struct libusb_config_descriptor {struct libusb_interface* interface; scalar_t__ bNumInterfaces; } ;
struct libusb_adapter {int interface_number; int endpoint_in; int endpoint_out; int /*<<< orphan*/  endpoint_out_max_size; int /*<<< orphan*/  endpoint_in_max_size; } ;

/* Variables and functions */
 scalar_t__ LIBUSB_CLASS_HID ; 
 int LIBUSB_ENDPOINT_DIR_MASK ; 
 int LIBUSB_ENDPOINT_IN ; 
 int LIBUSB_ENDPOINT_OUT ; 
 int LIBUSB_TRANSFER_TYPE_INTERRUPT ; 
 int LIBUSB_TRANSFER_TYPE_MASK ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 int /*<<< orphan*/  libusb_free_config_descriptor (struct libusb_config_descriptor*) ; 
 int libusb_get_config_descriptor (struct libusb_device*,int /*<<< orphan*/ ,struct libusb_config_descriptor**) ; 

__attribute__((used)) static void libusb_get_description(struct libusb_device *device,
      struct libusb_adapter *adapter)
{
   int j;
   unsigned i, k;
   struct libusb_config_descriptor *config;

   int desc_ret = libusb_get_config_descriptor(device, 0, &config);

   if (desc_ret != 0)
   {
      RARCH_ERR("Error %d getting libusb config descriptor\n", desc_ret);
      return;
   }

   for (i = 0; i < (int)config->bNumInterfaces; i++)
   {
      const struct libusb_interface *inter = &config->interface[i];

      for(j = 0; j < inter->num_altsetting; j++)
      {
         const struct libusb_interface_descriptor *interdesc =
            &inter->altsetting[j];

#if 0
         if (interdesc->bInterfaceClass == LIBUSB_CLASS_HID)
#endif
         {
            adapter->interface_number = (int)interdesc->bInterfaceNumber;

            for(k = 0; k < (int)interdesc->bNumEndpoints; k++)
            {
               const struct libusb_endpoint_descriptor *epdesc =
                  &interdesc->endpoint[k];
               bool is_int = (epdesc->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK)
                  == LIBUSB_TRANSFER_TYPE_INTERRUPT;
               bool is_out = (epdesc->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK)
                  == LIBUSB_ENDPOINT_OUT;
               bool is_in = (epdesc->bEndpointAddress & LIBUSB_ENDPOINT_DIR_MASK)
                  == LIBUSB_ENDPOINT_IN;

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
         }

         goto ret;
      }
   }

ret:
   libusb_free_config_descriptor(config);
}