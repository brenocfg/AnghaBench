#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * result; int /*<<< orphan*/  done_semaphore; } ;
typedef  TYPE_1__ mdns_search_once_t ;
typedef  int /*<<< orphan*/  mdns_result_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SEARCH_ADD ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  _mdns_search_free (TYPE_1__*) ; 
 TYPE_1__* _mdns_search_init (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ _mdns_send_search_action (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _mdns_server ; 
 scalar_t__ _str_null_or_empty (char const*) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t mdns_query(const char * name, const char * service, const char * proto, uint16_t type, uint32_t timeout, size_t max_results, mdns_result_t ** results)
{
    mdns_search_once_t * search = NULL;

    *results = NULL;

    if (!_mdns_server) {
        return ESP_ERR_INVALID_STATE;
    }

    if (!timeout || _str_null_or_empty(service) != _str_null_or_empty(proto)) {
        return ESP_ERR_INVALID_ARG;
    }

    search = _mdns_search_init(name, service, proto, type, timeout, max_results);
    if (!search) {
        return ESP_ERR_NO_MEM;
    }

    if (_mdns_send_search_action(ACTION_SEARCH_ADD, search)) {
        _mdns_search_free(search);
        return ESP_ERR_NO_MEM;
    }
    xSemaphoreTake(search->done_semaphore, portMAX_DELAY);

    *results = search->result;
    _mdns_search_free(search);

    return ESP_OK;
}