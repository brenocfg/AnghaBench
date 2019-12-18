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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  handle; } ;
struct btpad_queue_command {TYPE_1__ hci_disconnect; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_increment_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btpad_queue_process () ; 
 int /*<<< orphan*/  hci_disconnect_ptr ; 
 int /*<<< orphan*/  insert_position ; 

__attribute__((used)) static void btpad_queue_hci_disconnect(
      struct btpad_queue_command *cmd,
      uint16_t handle, uint8_t reason)
{
   if (!cmd)
      return;

   cmd->command               = hci_disconnect_ptr;
   cmd->hci_disconnect.handle = handle;
   cmd->hci_disconnect.reason = reason;

   btpad_increment_position(&insert_position);
   btpad_queue_process();
}