#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MDNS_SERVICE_LOCK () ; 
 int /*<<< orphan*/  MDNS_SERVICE_STACK_DEPTH ; 
 int /*<<< orphan*/  MDNS_SERVICE_UNLOCK () ; 
 int /*<<< orphan*/  MDNS_TASK_AFFINITY ; 
 int /*<<< orphan*/  MDNS_TASK_PRIORITY ; 
 int /*<<< orphan*/ * _mdns_service_semaphore ; 
 int /*<<< orphan*/  _mdns_service_task ; 
 int /*<<< orphan*/  _mdns_service_task_handle ; 
 scalar_t__ _mdns_start_timer () ; 
 int /*<<< orphan*/  _mdns_stop_timer () ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/  xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t _mdns_service_task_start(void)
{
    if (!_mdns_service_semaphore) {
        _mdns_service_semaphore = xSemaphoreCreateMutex();
        if (!_mdns_service_semaphore) {
            return ESP_FAIL;
        }
    }
    MDNS_SERVICE_LOCK();
    if (_mdns_start_timer()) {
        MDNS_SERVICE_UNLOCK();
        return ESP_FAIL;
    }
    if (!_mdns_service_task_handle) {
        xTaskCreatePinnedToCore(_mdns_service_task, "mdns", MDNS_SERVICE_STACK_DEPTH, NULL, MDNS_TASK_PRIORITY,
                                (TaskHandle_t * const)(&_mdns_service_task_handle), MDNS_TASK_AFFINITY);
        if (!_mdns_service_task_handle) {
            _mdns_stop_timer();
            MDNS_SERVICE_UNLOCK();
            vSemaphoreDelete(_mdns_service_semaphore);
            _mdns_service_semaphore = NULL;
            return ESP_FAIL;
        }
    }
    MDNS_SERVICE_UNLOCK();
    return ESP_OK;
}