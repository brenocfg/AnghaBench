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
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * s_wps_api_sem ; 
 int /*<<< orphan*/ * s_wps_data_lock ; 
 int /*<<< orphan*/ * s_wps_queue ; 
 int /*<<< orphan*/  s_wps_rxq ; 
 int /*<<< orphan*/ * s_wps_task_create_sem ; 
 int /*<<< orphan*/ * s_wps_task_hdl ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wps_rxq_deinit () ; 

int wps_task_deinit(void)
{
    wpa_printf(MSG_DEBUG, "wps task deinit");

    if (s_wps_api_sem) {
        vSemaphoreDelete(s_wps_api_sem);
        s_wps_api_sem = NULL;
        wpa_printf(MSG_DEBUG, "wps task deinit: free api sem");
    }

    if (s_wps_task_create_sem) {
        vSemaphoreDelete(s_wps_task_create_sem);
        s_wps_task_create_sem = NULL;
        wpa_printf(MSG_DEBUG, "wps task deinit: free task create sem");
    }

    if (s_wps_queue) {
        vQueueDelete(s_wps_queue);
        s_wps_queue = NULL;
        wpa_printf(MSG_DEBUG, "wps task deinit: free queue");
    }

    if (s_wps_task_hdl) {
        vTaskDelete(s_wps_task_hdl);
        s_wps_task_hdl = NULL;
        wpa_printf(MSG_DEBUG, "wps task deinit: free task");
    }

    if (STAILQ_FIRST(&s_wps_rxq) != NULL){
        wps_rxq_deinit();
    }

    if (s_wps_data_lock) {
        vSemaphoreDelete(s_wps_data_lock);
        s_wps_data_lock = NULL;
        wpa_printf(MSG_DEBUG, "wps task deinit: free data lock");
    }

    return ESP_OK;
}