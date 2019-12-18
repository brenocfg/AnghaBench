#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; int /*<<< orphan*/ * pop; scalar_t__ sec_ver; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ test_protocomm (TYPE_1__*) ; 

__attribute__((used)) static esp_err_t test_security0 (void)
{
    ESP_LOGI(TAG, "Starting Sec0 test");

    session_t *session = calloc(1, sizeof(session_t));
    if (session == NULL) {
        ESP_LOGE(TAG, "Error allocating session");
        return ESP_ERR_NO_MEM;
    }

    session->id        = 8;
    session->sec_ver   = 0;
    session->pop       = NULL;

    if (test_protocomm (session) != ESP_OK) {
        ESP_LOGE(TAG, "Sec0 test failed");
        free(session);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "Sec0 test successful");
    free(session);
    return ESP_OK;
}