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
struct btstack_hid_adapter {int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_send_l2cap_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void btpad_connection_send_control(void *data,
      uint8_t* data_buf, size_t size)
{
   struct btstack_hid_adapter *connection = (struct btstack_hid_adapter*)data;

   if (connection)
      bt_send_l2cap_ptr(connection->channels[0], data_buf, size);
}