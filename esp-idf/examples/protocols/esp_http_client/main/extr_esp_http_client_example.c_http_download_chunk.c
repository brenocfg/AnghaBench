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
typedef  int /*<<< orphan*/  esp_http_client_handle_t ;
struct TYPE_3__ {char* url; int /*<<< orphan*/  event_handler; } ;
typedef  TYPE_1__ esp_http_client_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  _http_event_handler ; 
 int /*<<< orphan*/  esp_err_to_name (scalar_t__) ; 
 int /*<<< orphan*/  esp_http_client_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_http_client_get_content_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_http_client_get_status_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_http_client_init (TYPE_1__*) ; 
 scalar_t__ esp_http_client_perform (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void http_download_chunk(void)
{
    esp_http_client_config_t config = {
        .url = "http://httpbin.org/stream-bytes/8912",
        .event_handler = _http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP chunk encoding Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "Error perform http request %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}