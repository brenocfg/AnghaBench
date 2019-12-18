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
struct btpad_queue_command {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_increment_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btpad_queue_process () ; 
 int /*<<< orphan*/  hci_read_bd_addr_ptr ; 
 int /*<<< orphan*/  insert_position ; 

__attribute__((used)) static void btpad_queue_hci_read_bd_addr(
      struct btpad_queue_command *cmd)
{
   if (!cmd)
      return;

   cmd->command = hci_read_bd_addr_ptr;

   btpad_increment_position(&insert_position);
   btpad_queue_process();
}