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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  clock_offset; void* reserved; void* page_scan_repetition_mode; int /*<<< orphan*/  bd_addr; } ;
struct btpad_queue_command {TYPE_1__ hci_remote_name_request; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  bd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  btpad_increment_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btpad_queue_process () ; 
 int /*<<< orphan*/  hci_remote_name_request_ptr ; 
 int /*<<< orphan*/  insert_position ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btpad_queue_hci_remote_name_request(
      struct btpad_queue_command *cmd,
      bd_addr_t bd_addr,
      uint8_t page_scan_repetition_mode,
      uint8_t reserved, uint16_t clock_offset)
{
   if (!cmd)
      return;

   cmd->command = hci_remote_name_request_ptr;
   memcpy(cmd->hci_remote_name_request.bd_addr, bd_addr, sizeof(bd_addr_t));
   cmd->hci_remote_name_request.page_scan_repetition_mode =
      page_scan_repetition_mode;
   cmd->hci_remote_name_request.reserved     = reserved;
   cmd->hci_remote_name_request.clock_offset = clock_offset;

   btpad_increment_position(&insert_position);
   btpad_queue_process();
}