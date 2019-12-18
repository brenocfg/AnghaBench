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
 int /*<<< orphan*/  esp_pthread_cfg_key_destructor ; 
 scalar_t__ pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_pthread_cfg_key ; 
 int /*<<< orphan*/ * s_threads_mux ; 
 int /*<<< orphan*/ * xSemaphoreCreateMutex () ; 

esp_err_t esp_pthread_init(void)
{
    if (pthread_key_create(&s_pthread_cfg_key, esp_pthread_cfg_key_destructor) != 0) {
        return ESP_ERR_NO_MEM;
    }
    s_threads_mux = xSemaphoreCreateMutex();
    if (s_threads_mux == NULL) {
        pthread_key_delete(s_pthread_cfg_key);
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}