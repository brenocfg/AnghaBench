#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  remove_endpoint; int /*<<< orphan*/  add_endpoint; } ;
typedef  TYPE_1__ protocomm_t ;
struct TYPE_7__ {int /*<<< orphan*/  task_priority; int /*<<< orphan*/  stack_size; } ;
typedef  TYPE_2__ protocomm_console_config_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  console_task ; 
 TYPE_1__* pc_console ; 
 scalar_t__ pdPASS ; 
 int /*<<< orphan*/  protocomm_console_add_endpoint ; 
 int /*<<< orphan*/  protocomm_console_remove_endpoint ; 
 int /*<<< orphan*/  protocomm_console_task ; 
 scalar_t__ xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

esp_err_t protocomm_console_start(protocomm_t *pc, const protocomm_console_config_t *config)
{
    if (pc == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (pc_console != NULL) {
        if (pc_console == pc) {
            return ESP_ERR_INVALID_STATE;
        }
        else {
            return ESP_ERR_NOT_SUPPORTED;
        }
    }


    if (xTaskCreate(protocomm_console_task, "protocomm_console",
                    config->stack_size, NULL, config->task_priority, &console_task) != pdPASS) {
        return ESP_FAIL;
    }

    pc->add_endpoint = protocomm_console_add_endpoint;
    pc->remove_endpoint = protocomm_console_remove_endpoint;
    pc_console = pc;
    return ESP_OK;
}