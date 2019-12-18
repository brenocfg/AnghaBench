#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  action_queue; } ;
typedef  TYPE_2__ mdns_server_t ;
typedef  int /*<<< orphan*/  mdns_action_t ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_9__ {TYPE_1__ ip; } ;
typedef  TYPE_3__ esp_netif_ip_info_t ;
typedef  int /*<<< orphan*/  esp_ip6_addr_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_EVENT_ANY_ID ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ETH_EVENT ; 
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int /*<<< orphan*/  IP_EVENT ; 
 int /*<<< orphan*/  MDNS_ACTION_QUEUE_LEN ; 
 scalar_t__ MDNS_IF_MAX ; 
 int /*<<< orphan*/  MDNS_IP_PROTOCOL_V4 ; 
 int /*<<< orphan*/  MDNS_IP_PROTOCOL_V6 ; 
 int /*<<< orphan*/  WIFI_EVENT ; 
 int /*<<< orphan*/  _ipv6_address_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_disable_pcb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_enable_pcb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_get_esp_netif (scalar_t__) ; 
 TYPE_2__* _mdns_server ; 
 scalar_t__ _mdns_service_task_start () ; 
 int /*<<< orphan*/  esp_event_handler_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_event_handler_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_get_ip6_linklocal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_netif_get_ip_info (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  event_handler ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xSemaphoreCreateMutex () ; 

esp_err_t mdns_init(void)
{
    esp_err_t err = ESP_OK;

    if (_mdns_server) {
        return err;
    }

    _mdns_server = (mdns_server_t *)malloc(sizeof(mdns_server_t));
    if (!_mdns_server) {
        HOOK_MALLOC_FAILED;
        return ESP_ERR_NO_MEM;
    }
    memset((uint8_t*)_mdns_server, 0, sizeof(mdns_server_t));

    _mdns_server->lock = xSemaphoreCreateMutex();
    if (!_mdns_server->lock) {
        err = ESP_ERR_NO_MEM;
        goto free_server;
    }

    _mdns_server->action_queue = xQueueCreate(MDNS_ACTION_QUEUE_LEN, sizeof(mdns_action_t *));
    if (!_mdns_server->action_queue) {
        err = ESP_ERR_NO_MEM;
        goto free_lock;
    }
    if ((err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL)) != ESP_OK) {
        goto free_event_handlers;
    }
    if ((err = esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL)) != ESP_OK) {
        goto free_event_handlers;
    }
#if CONFIG_ETH_ENABLED
    if ((err = esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL)) != ESP_OK) {
        goto free_event_handlers;
    }
#endif
    uint8_t i;
    esp_ip6_addr_t tmp_addr6;
    esp_netif_ip_info_t if_ip_info;

    for (i=0; i<MDNS_IF_MAX; i++) {
        if (!esp_netif_get_ip6_linklocal(_mdns_get_esp_netif(i), &tmp_addr6) && !_ipv6_address_is_zero(tmp_addr6)) {
            _mdns_enable_pcb(i, MDNS_IP_PROTOCOL_V6);
        }
        if (!esp_netif_get_ip_info(_mdns_get_esp_netif(i), &if_ip_info) && if_ip_info.ip.addr) {
            _mdns_enable_pcb(i, MDNS_IP_PROTOCOL_V4);
        }
    }

    if (_mdns_service_task_start()) {
        //service start failed!
        err = ESP_FAIL;
        goto free_all_and_disable_pcbs;
    }

    return ESP_OK;

free_all_and_disable_pcbs:
    for (i=0; i<MDNS_IF_MAX; i++) {
        _mdns_disable_pcb(i, MDNS_IP_PROTOCOL_V6);
        _mdns_disable_pcb(i, MDNS_IP_PROTOCOL_V4);
    }
free_event_handlers:
    esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler);
    esp_event_handler_unregister(IP_EVENT, ESP_EVENT_ANY_ID, &event_handler);
#if CONFIG_ETH_ENABLED
    esp_event_handler_unregister(ETH_EVENT, ESP_EVENT_ANY_ID, &event_handler);
#endif
    vQueueDelete(_mdns_server->action_queue);
free_lock:
    vSemaphoreDelete(_mdns_server->lock);
free_server:
    free(_mdns_server);
    _mdns_server = NULL;
    return err;
}