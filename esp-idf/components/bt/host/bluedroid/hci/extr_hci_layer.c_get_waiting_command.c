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
struct TYPE_7__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ waiting_command_t ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_8__ {int /*<<< orphan*/  commands_pending_response_lock; int /*<<< orphan*/  commands_pending_response; } ;
typedef  TYPE_2__ command_waiting_response_t ;
typedef  scalar_t__ command_opcode_t ;
struct TYPE_9__ {TYPE_2__ cmd_waiting_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 TYPE_5__ hci_host_env ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 TYPE_1__* list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static waiting_command_t *get_waiting_command(command_opcode_t opcode)
{
    command_waiting_response_t *cmd_wait_q = &hci_host_env.cmd_waiting_q;
    osi_mutex_lock(&cmd_wait_q->commands_pending_response_lock, OSI_MUTEX_MAX_TIMEOUT);

    for (const list_node_t *node = list_begin(cmd_wait_q->commands_pending_response);
            node != list_end(cmd_wait_q->commands_pending_response);
            node = list_next(node)) {
        waiting_command_t *wait_entry = list_node(node);
        if (!wait_entry || wait_entry->opcode != opcode) {
            continue;
        }

        list_remove(cmd_wait_q->commands_pending_response, wait_entry);

        osi_mutex_unlock(&cmd_wait_q->commands_pending_response_lock);
        return wait_entry;
    }

    osi_mutex_unlock(&cmd_wait_q->commands_pending_response_lock);
    return NULL;
}