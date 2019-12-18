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
typedef  int /*<<< orphan*/  esp_pthread_cfg_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_pthread_cfg_key ; 

esp_err_t esp_pthread_get_cfg(esp_pthread_cfg_t *p)
{
    esp_pthread_cfg_t *cfg = pthread_getspecific(s_pthread_cfg_key);
    if (cfg) {
        *p = *cfg;
        return ESP_OK;
    }
    memset(p, 0, sizeof(*p));
    return ESP_ERR_NOT_FOUND;
}