#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  portTickType ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mdns_action_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  action_queue; int /*<<< orphan*/  services; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SERVICES_CLEAR ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 TYPE_4__* _mdns_server ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pdPASS ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 

esp_err_t mdns_service_remove_all(void)
{
    if (!_mdns_server) {
        return ESP_ERR_INVALID_ARG;
    }
    if (!_mdns_server->services) {
        return ESP_OK;
    }

    mdns_action_t * action = (mdns_action_t *)malloc(sizeof(mdns_action_t));
    if (!action) {
        HOOK_MALLOC_FAILED;
        return ESP_ERR_NO_MEM;
    }
    action->type = ACTION_SERVICES_CLEAR;
    if (xQueueSend(_mdns_server->action_queue, &action, (portTickType)0) != pdPASS) {
        free(action);
        return ESP_ERR_NO_MEM;
    }
    return ESP_OK;
}