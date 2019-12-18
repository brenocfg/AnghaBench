#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int timer_is_set; int /*<<< orphan*/  commands_pending_response_lock; int /*<<< orphan*/  command_response_timer; int /*<<< orphan*/  commands_pending_response; } ;
typedef  TYPE_1__ command_waiting_response_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_PENDING_TIMEOUT ; 
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_alarm_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_alarm_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void restart_command_waiting_response_timer(command_waiting_response_t *cmd_wait_q)
{
    osi_mutex_lock(&cmd_wait_q->commands_pending_response_lock, OSI_MUTEX_MAX_TIMEOUT);
    if (cmd_wait_q->timer_is_set) {
        osi_alarm_cancel(cmd_wait_q->command_response_timer);
        cmd_wait_q->timer_is_set = false;
    }
    if (!list_is_empty(cmd_wait_q->commands_pending_response)) {
        osi_alarm_set(cmd_wait_q->command_response_timer, COMMAND_PENDING_TIMEOUT);
        cmd_wait_q->timer_is_set = true;
    }
    osi_mutex_unlock(&cmd_wait_q->commands_pending_response_lock);
}