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
typedef  int /*<<< orphan*/  esp_http_client_handle_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ _http_handle_response_code (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_err_to_name (scalar_t__) ; 
 int esp_http_client_fetch_headers (int /*<<< orphan*/ ) ; 
 int esp_http_client_get_status_code (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_http_client_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ process_again (int) ; 

__attribute__((used)) static esp_err_t _http_connect(esp_http_client_handle_t http_client)
{
    esp_err_t err = ESP_FAIL;
    int status_code, header_ret;
    do {
        err = esp_http_client_open(http_client, 0);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
            return err;
        }
        header_ret = esp_http_client_fetch_headers(http_client);
        if (header_ret < 0) {
            return header_ret;
        }
        status_code = esp_http_client_get_status_code(http_client);
        err = _http_handle_response_code(http_client, status_code);
        if (err != ESP_OK) {
            return err;
        }
    } while (process_again(status_code));
    return err;
}