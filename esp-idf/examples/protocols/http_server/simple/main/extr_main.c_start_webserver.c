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
struct TYPE_4__ {int /*<<< orphan*/  server_port; } ;
typedef  TYPE_1__ httpd_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 TYPE_1__ HTTPD_DEFAULT_CONFIG () ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  ctrl ; 
 int /*<<< orphan*/  echo ; 
 int /*<<< orphan*/  hello ; 
 int /*<<< orphan*/  httpd_register_uri_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ httpd_start (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &hello);
        httpd_register_uri_handler(server, &echo);
        httpd_register_uri_handler(server, &ctrl);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}