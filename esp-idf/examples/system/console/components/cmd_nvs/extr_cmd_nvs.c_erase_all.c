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
typedef  int /*<<< orphan*/  nvs_handle_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  NVS_READWRITE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_commit (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_erase_all (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t erase_all(const char *name)
{
    nvs_handle_t nvs;

    esp_err_t err = nvs_open(name, NVS_READWRITE, &nvs);
    if (err == ESP_OK) {
        err = nvs_erase_all(nvs);
        if (err == ESP_OK) {
            err = nvs_commit(nvs);
        }
    }

    ESP_LOGI(TAG, "Namespace '%s' was %s erased", name, (err == ESP_OK) ? "" : "not");

    nvs_close(nvs);
    return ESP_OK;
}