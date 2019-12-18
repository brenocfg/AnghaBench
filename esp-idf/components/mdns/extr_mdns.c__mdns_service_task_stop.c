#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  portTickType ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mdns_action_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  action_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_TASK_STOP ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__* _mdns_server ; 
 int /*<<< orphan*/ * _mdns_service_semaphore ; 
 int /*<<< orphan*/ * _mdns_service_task_handle ; 
 int /*<<< orphan*/  _mdns_stop_timer () ; 
 scalar_t__ pdPASS ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t _mdns_service_task_stop(void)
{
    _mdns_stop_timer();
    if (_mdns_service_task_handle) {
        mdns_action_t action;
        mdns_action_t * a = &action;
        action.type = ACTION_TASK_STOP;
        if (xQueueSend(_mdns_server->action_queue, &a, (portTickType)0) != pdPASS) {
            vTaskDelete(_mdns_service_task_handle);
            _mdns_service_task_handle = NULL;
        }
        while (_mdns_service_task_handle) {
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
    vSemaphoreDelete(_mdns_service_semaphore);
    _mdns_service_semaphore = NULL;
    return ESP_OK;
}