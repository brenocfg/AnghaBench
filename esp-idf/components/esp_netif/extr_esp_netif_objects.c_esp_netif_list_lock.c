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
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/ * s_list_lock ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

esp_err_t esp_netif_list_lock(void)
{
    if (s_list_lock == NULL) {
        s_list_lock = xSemaphoreCreateMutex();
        if (s_list_lock == NULL) {
            return ESP_ERR_NO_MEM;
        }
    }
    xSemaphoreTake(s_list_lock, portMAX_DELAY);
    return ESP_OK;
}