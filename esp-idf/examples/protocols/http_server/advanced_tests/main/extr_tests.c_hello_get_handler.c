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
typedef  int /*<<< orphan*/  httpd_req_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  STR ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  httpd_resp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uxTaskGetStackHighWaterMark (int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t hello_get_handler(httpd_req_t *req)
{
#define STR "Hello World!"
    ESP_LOGI(TAG, "Free Stack for server task: '%d'", uxTaskGetStackHighWaterMark(NULL));
    httpd_resp_send(req, STR, strlen(STR));
    return ESP_OK;
#undef STR
}