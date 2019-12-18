#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_VER_STR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ protocomm_req_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_pc ; 

__attribute__((used)) static esp_err_t test_ver_endpoint(session_t *session)
{
    ssize_t  ver_data_len = 0;
    uint8_t *ver_data = NULL;

    esp_err_t ret = protocomm_req_handle(test_pc, "test-ver", session->id,
                                         NULL, 0, &ver_data, &ver_data_len);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "test-ver handler failed");
        return ESP_FAIL;
    }

    if (ver_data_len != strlen(TEST_VER_STR) || memcmp(TEST_VER_STR, ver_data, ver_data_len)) {
        ESP_LOGE(TAG, "incorrect response data from test-ver");
        free(ver_data);
        return ESP_FAIL;
    }
    free(ver_data);
    return ESP_OK;
}