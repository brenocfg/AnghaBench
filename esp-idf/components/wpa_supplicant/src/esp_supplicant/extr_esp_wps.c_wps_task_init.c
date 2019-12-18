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

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  SIG_WPS_NUM ; 
 int /*<<< orphan*/  WPS_TASK_STACK_SIZE ; 
 int /*<<< orphan*/  os_bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pdPASS ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 void* s_wps_api_sem ; 
 int /*<<< orphan*/  s_wps_data_lock ; 
 int /*<<< orphan*/  s_wps_queue ; 
 int /*<<< orphan*/  s_wps_sig_cnt ; 
 int /*<<< orphan*/ * s_wps_task_create_sem ; 
 int /*<<< orphan*/  s_wps_task_hdl ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wps_rxq_init () ; 
 int /*<<< orphan*/  wps_task ; 
 int /*<<< orphan*/  wps_task_deinit () ; 
 int /*<<< orphan*/  xQueueCreate (int /*<<< orphan*/ ,int) ; 
 void* xSemaphoreCreateCounting (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xSemaphoreCreateRecursiveMutex () ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xTaskCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int wps_task_init(void)
{
    int ret = 0;

    /* Call wps_task_deinit() first in case esp_wifi_wps_disable() fails
     */
    wps_task_deinit();

    s_wps_data_lock = xSemaphoreCreateRecursiveMutex();
    if (!s_wps_data_lock) {
        wpa_printf(MSG_ERROR, "wps task init: failed to alloc data lock");
        goto _wps_no_mem;
    }

    s_wps_api_sem = xSemaphoreCreateCounting(1, 0);
    if (!s_wps_api_sem) {
        wpa_printf(MSG_ERROR, "wps task init: failed to create api sem");
        goto _wps_no_mem;
    }

    s_wps_task_create_sem = xSemaphoreCreateCounting(1, 0);
    if (!s_wps_task_create_sem) {
        wpa_printf(MSG_ERROR, "wps task init: failed to create task sem");
        goto _wps_no_mem;
    }

    os_bzero(s_wps_sig_cnt, SIG_WPS_NUM);
    s_wps_queue = xQueueCreate(SIG_WPS_NUM, sizeof( void * ) );
    if (!s_wps_queue) {
        wpa_printf(MSG_ERROR, "wps task init: failed to alloc queue");
        goto _wps_no_mem;
    }

    wps_rxq_init();

    ret = xTaskCreate(wps_task, "wpsT", WPS_TASK_STACK_SIZE, NULL, 2, &s_wps_task_hdl);
    if (pdPASS != ret) {
        wpa_printf(MSG_ERROR, "wps enable: failed to create task");
        goto _wps_no_mem;
    }

    xSemaphoreTake(s_wps_task_create_sem, portMAX_DELAY);
    vSemaphoreDelete(s_wps_task_create_sem);
    s_wps_task_create_sem = NULL;

    wpa_printf(MSG_DEBUG, "wifi wps enable: task prio:%d, stack:%d", 2, WPS_TASK_STACK_SIZE);
    return ESP_OK;

_wps_no_mem:
    wps_task_deinit();
    return ESP_ERR_NO_MEM;
}