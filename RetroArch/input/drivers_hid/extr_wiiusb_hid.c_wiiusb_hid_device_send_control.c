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
typedef  int /*<<< orphan*/  uint8_t ;
struct wiiusb_adapter {size_t send_control_size; int /*<<< orphan*/  send_control_type; int /*<<< orphan*/  send_control_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void wiiusb_hid_device_send_control(void *data,
      uint8_t* data_buf, size_t size)
{
   uint8_t control_type;
   struct wiiusb_adapter *adapter = (struct wiiusb_adapter*)data;
   if (!adapter || !data_buf || !adapter->send_control_buffer)
      return;

   /* first byte contains the type of control to use
    * which can be NONE, INT_MSG, CTRL_MSG, CTRL_MSG2 */
   control_type = data_buf[0];
   /* decrement size by one as we are getting rid of first byte */
   adapter->send_control_size = size - 1;
   /* increase the buffer address so we access the actual data */
   data_buf++;
   memcpy(adapter->send_control_buffer, data_buf,  adapter->send_control_size);
   /* Activate it so it can be processed in the adapter thread */
   adapter->send_control_type = control_type;
}