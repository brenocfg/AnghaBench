#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct libusb_adapter {size_t* data; size_t endpoint_in_max_size; size_t slot; int /*<<< orphan*/  endpoint_in; int /*<<< orphan*/  handle; int /*<<< orphan*/  send_control_lock; int /*<<< orphan*/  endpoint_out; int /*<<< orphan*/  send_control_buffer; int /*<<< orphan*/  quitting; TYPE_1__* hid; } ;
typedef  int /*<<< orphan*/  send_command_size ;
struct TYPE_2__ {int /*<<< orphan*/ * slots; } ;
typedef  TYPE_1__ libusb_hid_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libusb_interrupt_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t,int*,int) ; 
 int /*<<< orphan*/  pad_connection_packet (int /*<<< orphan*/ *,size_t,size_t*,int) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adapter_thread(void *data)
{
   uint8_t send_command_buf[4096];
   struct libusb_adapter *adapter = (struct libusb_adapter*)data;
   libusb_hid_t *hid              = adapter ? adapter->hid : NULL;

   if (!adapter)
      return;

   while (!adapter->quitting)
   {
      size_t send_command_size;
      int tmp;
      int report_number;
      int size = 0;

      slock_lock(adapter->send_control_lock);
      if (fifo_read_avail(adapter->send_control_buffer)
            >= sizeof(send_command_size))
      {
         fifo_read(adapter->send_control_buffer,
               &send_command_size, sizeof(send_command_size));

         if (fifo_read_avail(adapter->send_control_buffer)
               >= sizeof(send_command_size))
         {
            fifo_read(adapter->send_control_buffer,
                  send_command_buf, send_command_size);
            libusb_interrupt_transfer(adapter->handle,
                  adapter->endpoint_out, send_command_buf,
                  send_command_size, &tmp, 1000);
         }
      }
      slock_unlock(adapter->send_control_lock);

      libusb_interrupt_transfer(adapter->handle,
            adapter->endpoint_in, &adapter->data[1],
            adapter->endpoint_in_max_size, &size, 1000);

      if (adapter && hid && hid->slots && size)
         pad_connection_packet(&hid->slots[adapter->slot], adapter->slot,
               adapter->data, size+1);
   }
}