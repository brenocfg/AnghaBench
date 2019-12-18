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

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  IPERF_REPORT_TASK_NAME ; 
 int /*<<< orphan*/  IPERF_REPORT_TASK_PRIORITY ; 
 int /*<<< orphan*/  IPERF_REPORT_TASK_STACK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  iperf_report_task ; 
 int pdPASS ; 
 scalar_t__ portNUM_PROCESSORS ; 
 int xTaskCreatePinnedToCore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static esp_err_t iperf_start_report(void)
{
    int ret;

    ret = xTaskCreatePinnedToCore(iperf_report_task, IPERF_REPORT_TASK_NAME, IPERF_REPORT_TASK_STACK, NULL, IPERF_REPORT_TASK_PRIORITY, NULL, portNUM_PROCESSORS - 1);

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "create task %s failed", IPERF_REPORT_TASK_NAME);
        return ESP_FAIL;
    }

    return ESP_OK;
}