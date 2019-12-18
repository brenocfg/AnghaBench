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
typedef  int /*<<< orphan*/  protocomm_req_handler_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 

__attribute__((used)) static esp_err_t protocomm_ble_add_endpoint(const char *ep_name,
                                            protocomm_req_handler_t req_handler,
                                            void *priv_data)
{
    /* Endpoint UUID already added when protocomm_ble_start() was called */
    return ESP_OK;
}