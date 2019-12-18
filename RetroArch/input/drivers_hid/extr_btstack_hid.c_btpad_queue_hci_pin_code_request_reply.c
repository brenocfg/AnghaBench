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
struct TYPE_2__ {int /*<<< orphan*/  pin; int /*<<< orphan*/  bd_addr; } ;
struct btpad_queue_command {TYPE_1__ hci_pin_code_request_reply; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  bd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_increment_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btpad_queue_process () ; 
 int /*<<< orphan*/  hci_pin_code_request_reply_ptr ; 
 int /*<<< orphan*/  insert_position ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btpad_queue_hci_pin_code_request_reply(
      struct btpad_queue_command *cmd,
      bd_addr_t bd_addr, bd_addr_t pin)
{
   if (!cmd)
      return;

   cmd->command = hci_pin_code_request_reply_ptr;
   memcpy(cmd->hci_pin_code_request_reply.bd_addr, bd_addr, sizeof(bd_addr_t));
   memcpy(cmd->hci_pin_code_request_reply.pin, pin, sizeof(bd_addr_t));

   btpad_increment_position(&insert_position);
   btpad_queue_process();
}