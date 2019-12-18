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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {void* num_responses; void* length; int /*<<< orphan*/  lap; } ;
struct btpad_queue_command {TYPE_1__ hci_inquiry; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_increment_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btpad_queue_process () ; 
 int /*<<< orphan*/  hci_inquiry_ptr ; 
 int /*<<< orphan*/  insert_position ; 

__attribute__((used)) static void btpad_queue_hci_inquiry(
      struct btpad_queue_command *cmd,
      uint32_t lap,
      uint8_t length, uint8_t num_responses)
{
   if (!cmd)
      return;

   cmd->command                   = hci_inquiry_ptr;
   cmd->hci_inquiry.lap           = lap;
   cmd->hci_inquiry.length        = length;
   cmd->hci_inquiry.num_responses = num_responses;

   btpad_increment_position(&insert_position);
   btpad_queue_process();
}