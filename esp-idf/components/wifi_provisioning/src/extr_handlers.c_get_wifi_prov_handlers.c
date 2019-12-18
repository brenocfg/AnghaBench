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
struct TYPE_3__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  apply_config_handler; int /*<<< orphan*/  set_config_handler; int /*<<< orphan*/  get_status_handler; } ;
typedef  TYPE_1__ wifi_prov_config_handlers_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  apply_config_handler ; 
 int /*<<< orphan*/  get_status_handler ; 
 int /*<<< orphan*/  set_config_handler ; 

esp_err_t get_wifi_prov_handlers(wifi_prov_config_handlers_t *ptr)
{
    if (!ptr) {
        return ESP_ERR_INVALID_ARG;
    }
    ptr->get_status_handler   = get_status_handler;
    ptr->set_config_handler   = set_config_handler;
    ptr->apply_config_handler = apply_config_handler;
    ptr->ctx = NULL;
    return ESP_OK;
}