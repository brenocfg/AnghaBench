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
struct libusb_hid {int /*<<< orphan*/ * slots; } ;
struct libusb_device {int dummy; } ;
struct libusb_adapter {size_t slot; int quitting; struct libusb_adapter* next; int /*<<< orphan*/  handle; int /*<<< orphan*/  interface_number; int /*<<< orphan*/  send_control_buffer; int /*<<< orphan*/  send_control_lock; int /*<<< orphan*/  thread; scalar_t__ name; struct libusb_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapters ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct libusb_adapter*) ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (size_t,char const*) ; 
 int /*<<< orphan*/  libusb_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_release_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_connection_pad_deinit (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_adapter(void *data, struct libusb_device *dev)
{
   struct libusb_adapter  *adapter = (struct libusb_adapter*)&adapters;
   struct libusb_hid          *hid = (struct libusb_hid*)data;

   while (adapter->next == NULL)
      return -1;

   if (adapter->next->device == dev)
   {
      struct libusb_adapter *new_next = NULL;
      const char                *name = (const char*)adapter->next->name;

      input_autoconfigure_disconnect(adapter->slot, name);

      adapter->next->quitting = true;
      sthread_join(adapter->next->thread);

      pad_connection_pad_deinit(&hid->slots[adapter->slot], adapter->slot);

      slock_free(adapter->send_control_lock);
      fifo_free(adapter->send_control_buffer);

      libusb_release_interface(adapter->next->handle,
            adapter->next->interface_number);
      libusb_close(adapter->next->handle);

      new_next = adapter->next->next;
      free(adapter->next);
      adapter->next = new_next;

      return 0;
   }

   return -1;
}