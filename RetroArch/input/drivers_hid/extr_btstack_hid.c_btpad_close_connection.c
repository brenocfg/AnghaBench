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
struct btstack_hid_adapter {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_queue_hci_disconnect (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/ * commands ; 
 size_t insert_position ; 
 int /*<<< orphan*/  memset (struct btstack_hid_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btpad_close_connection(struct btstack_hid_adapter* connection)
{
   if (!connection)
      return;

   if (connection->handle)
      btpad_queue_hci_disconnect(&commands[insert_position],
            connection->handle, 0x15);

   memset(connection, 0, sizeof(struct btstack_hid_adapter));
}