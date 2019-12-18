#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * command_response_timer; int /*<<< orphan*/  commands_pending_response_lock; int /*<<< orphan*/  commands_pending_response; } ;
typedef  TYPE_1__ command_waiting_response_t ;
struct TYPE_4__ {TYPE_1__ cmd_waiting_q; scalar_t__ packet_queue; scalar_t__ command_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_queue_free (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ hci_host_env ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_alarm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free_func ; 
 int /*<<< orphan*/  osi_mutex_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_layer_deinit_env(void)
{
    command_waiting_response_t *cmd_wait_q;

    if (hci_host_env.command_queue) {
        fixed_queue_free(hci_host_env.command_queue, osi_free_func);
    }
    if (hci_host_env.packet_queue) {
        fixed_queue_free(hci_host_env.packet_queue, osi_free_func);
    }

    cmd_wait_q = &hci_host_env.cmd_waiting_q;
    list_free(cmd_wait_q->commands_pending_response);
    osi_mutex_free(&cmd_wait_q->commands_pending_response_lock);
    osi_alarm_free(cmd_wait_q->command_response_timer);
    cmd_wait_q->command_response_timer = NULL;
}