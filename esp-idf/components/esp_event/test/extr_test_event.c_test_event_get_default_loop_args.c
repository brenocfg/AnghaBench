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
struct TYPE_3__ {char* task_name; int task_stack_size; int /*<<< orphan*/  task_core_id; int /*<<< orphan*/  task_priority; int /*<<< orphan*/  queue_size; } ;
typedef  TYPE_1__ esp_event_loop_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  s_test_priority ; 
 int /*<<< orphan*/  test_event_get_core () ; 

__attribute__((used)) static esp_event_loop_args_t test_event_get_default_loop_args(void)
{
    esp_event_loop_args_t loop_config = {
        .queue_size = CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE,
        .task_name = "loop",
        .task_priority = s_test_priority,
        .task_stack_size = 2048,
        .task_core_id = test_event_get_core()
    };

    return loop_config;
}