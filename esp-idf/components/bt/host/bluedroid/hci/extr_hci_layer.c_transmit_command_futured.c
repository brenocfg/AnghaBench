#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* command; int /*<<< orphan*/ * complete_future; int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ waiting_command_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  future_t ;
struct TYPE_9__ {int /*<<< orphan*/  command_queue; } ;
struct TYPE_8__ {int offset; int /*<<< orphan*/  event; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  MSG_STACK_TO_HC_HCI_CMD ; 
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * future_new () ; 
 TYPE_5__ hci_host_env ; 
 int /*<<< orphan*/  hci_host_task_post (int /*<<< orphan*/ ) ; 
 TYPE_1__* osi_calloc (int) ; 

__attribute__((used)) static future_t *transmit_command_futured(BT_HDR *command)
{
    waiting_command_t *wait_entry = osi_calloc(sizeof(waiting_command_t));
    assert(wait_entry != NULL);

    future_t *future = future_new();

    uint8_t *stream = command->data + command->offset;
    STREAM_TO_UINT16(wait_entry->opcode, stream);
    wait_entry->complete_future = future;
    wait_entry->command = command;

    // Store the command message type in the event field
    // in case the upper layer didn't already
    command->event = MSG_STACK_TO_HC_HCI_CMD;

    fixed_queue_enqueue(hci_host_env.command_queue, wait_entry, FIXED_QUEUE_MAX_TIMEOUT);
    hci_host_task_post(OSI_THREAD_MAX_TIMEOUT);
    return future;
}