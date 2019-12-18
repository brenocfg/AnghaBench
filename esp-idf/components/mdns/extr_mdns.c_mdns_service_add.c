#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  portTickType ;
typedef  int /*<<< orphan*/  mdns_txt_item_t ;
struct TYPE_9__ {TYPE_3__* service; } ;
struct TYPE_10__ {TYPE_1__ srv_add; } ;
struct TYPE_11__ {TYPE_2__ data; int /*<<< orphan*/  type; int /*<<< orphan*/ * next; int /*<<< orphan*/ * service; } ;
typedef  TYPE_3__ mdns_srv_item_t ;
typedef  int /*<<< orphan*/  mdns_service_t ;
typedef  TYPE_3__ mdns_action_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_12__ {int /*<<< orphan*/  action_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SERVICE_ADD ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int /*<<< orphan*/  MDNS_SERVICE_ADD_TIMEOUT_MS ; 
 int /*<<< orphan*/  MIN (int,size_t) ; 
 int /*<<< orphan*/  _mdns_can_add_more_services () ; 
 int /*<<< orphan*/ * _mdns_create_service (char const*,char const*,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mdns_free_service (int /*<<< orphan*/ *) ; 
 TYPE_3__* _mdns_get_service_item (char const*,char const*) ; 
 TYPE_7__* _mdns_server ; 
 scalar_t__ _str_null_or_empty (char const*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ malloc (int) ; 
 size_t pdMS_TO_TICKS (int /*<<< orphan*/ ) ; 
 scalar_t__ pdPASS ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int /*<<< orphan*/ ) ; 
 scalar_t__ xQueueSend (int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ ) ; 
 size_t xTaskGetTickCount () ; 

esp_err_t mdns_service_add(const char * instance, const char * service, const char * proto, uint16_t port, mdns_txt_item_t txt[], size_t num_items)
{
    if (!_mdns_server || _str_null_or_empty(service) || _str_null_or_empty(proto) || !port) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!_mdns_can_add_more_services()) {
        return ESP_ERR_NO_MEM;
    }

    mdns_srv_item_t * item = _mdns_get_service_item(service, proto);
    if (item) {
        return ESP_ERR_INVALID_ARG;
    }

    mdns_service_t * s = _mdns_create_service(service, proto, port, instance, num_items, txt);
    if (!s) {
        return ESP_ERR_NO_MEM;
    }

    item = (mdns_srv_item_t *)malloc(sizeof(mdns_srv_item_t));
    if (!item) {
        HOOK_MALLOC_FAILED;
        _mdns_free_service(s);
        return ESP_ERR_NO_MEM;
    }

    item->service = s;
    item->next = NULL;

    mdns_action_t * action = (mdns_action_t *)malloc(sizeof(mdns_action_t));
    if (!action) {
        HOOK_MALLOC_FAILED;
        _mdns_free_service(s);
        free(item);
        return ESP_ERR_NO_MEM;
    }
    action->type = ACTION_SERVICE_ADD;
    action->data.srv_add.service = item;
    if (xQueueSend(_mdns_server->action_queue, &action, (portTickType)0) != pdPASS) {
        _mdns_free_service(s);
        free(item);
        free(action);
        return ESP_ERR_NO_MEM;
    }

    size_t start = xTaskGetTickCount();
    size_t timeout_ticks = pdMS_TO_TICKS(MDNS_SERVICE_ADD_TIMEOUT_MS);
    while (_mdns_get_service_item(service, proto) == NULL)
    {
        uint32_t expired = xTaskGetTickCount() - start;
        if (expired >= timeout_ticks) {
            return ESP_FAIL; // Timeout
        }
        vTaskDelay(MIN(10 / portTICK_RATE_MS, timeout_ticks - expired));
    }

    return ESP_OK;
}