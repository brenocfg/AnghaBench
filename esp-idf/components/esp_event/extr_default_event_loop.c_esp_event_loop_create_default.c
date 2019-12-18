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
struct TYPE_3__ {char* task_name; int /*<<< orphan*/  task_core_id; int /*<<< orphan*/  task_priority; int /*<<< orphan*/  task_stack_size; int /*<<< orphan*/  queue_size; } ;
typedef  TYPE_1__ esp_event_loop_args_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_TASKD_EVENT_PRIO ; 
 int /*<<< orphan*/  ESP_TASKD_EVENT_STACK ; 
 scalar_t__ esp_event_loop_create (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ s_default_loop ; 

esp_err_t esp_event_loop_create_default(void)
{
    if (s_default_loop) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_event_loop_args_t loop_args = {
        .queue_size = CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE,
        .task_name = "sys_evt",
        .task_stack_size = ESP_TASKD_EVENT_STACK,
        .task_priority = ESP_TASKD_EVENT_PRIO,
        .task_core_id = 0
    };

    esp_err_t err;

    err = esp_event_loop_create(&loop_args, &s_default_loop);
    if (err != ESP_OK) {
        return err;
    }

    return ESP_OK;
}