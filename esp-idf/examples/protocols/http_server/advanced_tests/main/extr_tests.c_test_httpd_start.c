#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * httpd_handle_t ;
struct TYPE_4__ {int max_uri_handlers; int server_port; int max_open_sockets; int stack_size; } ;
typedef  TYPE_1__ httpd_config_t ;

/* Variables and functions */
 int CONFIG_LWIP_MAX_SOCKETS ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ESP_OK ; 
 TYPE_1__ HTTPD_DEFAULT_CONFIG () ; 
 int HTTPD_MAX_REQ_HDR_LEN ; 
 int HTTPD_MAX_URI_LEN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_get_free_heap_size () ; 
 scalar_t__ httpd_start (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  pre_start_mem ; 

__attribute__((used)) static httpd_handle_t test_httpd_start(void)
{
    pre_start_mem = esp_get_free_heap_size();
    httpd_handle_t hd;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    /* Modify this setting to match the number of test URI handlers */
    config.max_uri_handlers  = 9;
    config.server_port = 1234;

    /* This check should be a part of http_server */
    config.max_open_sockets = (CONFIG_LWIP_MAX_SOCKETS - 3);

    if (httpd_start(&hd, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Started HTTP server on port: '%d'", config.server_port);
        ESP_LOGI(TAG, "Max URI handlers: '%d'", config.max_uri_handlers);
        ESP_LOGI(TAG, "Max Open Sessions: '%d'", config.max_open_sockets);
        ESP_LOGI(TAG, "Max Header Length: '%d'", HTTPD_MAX_REQ_HDR_LEN);
        ESP_LOGI(TAG, "Max URI Length: '%d'", HTTPD_MAX_URI_LEN);
        ESP_LOGI(TAG, "Max Stack Size: '%d'", config.stack_size);
        return hd;
    }
    return NULL;
}