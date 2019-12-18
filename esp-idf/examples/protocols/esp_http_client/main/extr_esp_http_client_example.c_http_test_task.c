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
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  http_absolute_redirect () ; 
 int /*<<< orphan*/  http_auth_basic () ; 
 int /*<<< orphan*/  http_auth_basic_redirect () ; 
 int /*<<< orphan*/  http_auth_digest () ; 
 int /*<<< orphan*/  http_download_chunk () ; 
 int /*<<< orphan*/  http_perform_as_stream_reader () ; 
 int /*<<< orphan*/  http_redirect_to_https () ; 
 int /*<<< orphan*/  http_relative_redirect () ; 
 int /*<<< orphan*/  http_rest_with_hostname_path () ; 
 int /*<<< orphan*/  http_rest_with_url () ; 
 int /*<<< orphan*/  https_async () ; 
 int /*<<< orphan*/  https_with_hostname_path () ; 
 int /*<<< orphan*/  https_with_invalid_url () ; 
 int /*<<< orphan*/  https_with_url () ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void http_test_task(void *pvParameters)
{
    http_rest_with_url();
    http_rest_with_hostname_path();
    http_auth_basic();
    http_auth_basic_redirect();
    http_auth_digest();
    http_relative_redirect();
    http_absolute_redirect();
    https_with_url();
    https_with_hostname_path();
    http_redirect_to_https();
    http_download_chunk();
    http_perform_as_stream_reader();
    https_async();
    https_with_invalid_url();

    ESP_LOGI(TAG, "Finish http example");
    vTaskDelete(NULL);
}