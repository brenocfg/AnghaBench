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
typedef  size_t uint8_t ;
struct libusb_adapter {int /*<<< orphan*/  send_control_lock; int /*<<< orphan*/  send_control_buffer; } ;
typedef  int /*<<< orphan*/  size ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,size_t*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void libusb_hid_device_send_control(void *data,
      uint8_t* data_buf, size_t size)
{
   struct libusb_adapter *adapter = (struct libusb_adapter*)data;

   if (!adapter)
      return;

   slock_lock(adapter->send_control_lock);

   if (fifo_write_avail(adapter->send_control_buffer) >= size + sizeof(size))
   {
      fifo_write(adapter->send_control_buffer, &size, sizeof(size));
      fifo_write(adapter->send_control_buffer, data_buf, size);
   }
   else
   {
      RARCH_WARN("adapter write buffer is full, cannot write send control\n");
   }
   slock_unlock(adapter->send_control_lock);
}