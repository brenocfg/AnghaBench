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
struct TYPE_3__ {int inherit_cfg; int /*<<< orphan*/  pin_to_core; int /*<<< orphan*/ * thread_name; int /*<<< orphan*/  prio; int /*<<< orphan*/  stack_size; } ;
typedef  TYPE_1__ esp_pthread_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PTHREAD_TASK_PRIO_DEFAULT ; 
 int /*<<< orphan*/  CONFIG_PTHREAD_TASK_STACK_SIZE_DEFAULT ; 
 int /*<<< orphan*/  get_default_pthread_core () ; 

esp_pthread_cfg_t esp_pthread_get_default_config(void)
{
    esp_pthread_cfg_t cfg = {
        .stack_size = CONFIG_PTHREAD_TASK_STACK_SIZE_DEFAULT,
        .prio = CONFIG_PTHREAD_TASK_PRIO_DEFAULT,
        .inherit_cfg = false,
        .thread_name = NULL,
        .pin_to_core = get_default_pthread_core()
    };

    return cfg;
}