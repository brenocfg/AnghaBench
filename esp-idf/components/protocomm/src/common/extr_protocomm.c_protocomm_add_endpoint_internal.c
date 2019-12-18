#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {scalar_t__ (* add_endpoint ) (char const*,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  endpoints; } ;
typedef  TYPE_1__ protocomm_t ;
typedef  int /*<<< orphan*/ * protocomm_req_handler_t ;
struct TYPE_8__ {char const* ep_name; int /*<<< orphan*/  flag; void* priv_data; int /*<<< orphan*/ * req_handler; } ;
typedef  TYPE_2__ protocomm_ep_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  next ; 
 TYPE_2__* search_endpoint (TYPE_1__*,char const*) ; 
 scalar_t__ stub1 (char const*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static esp_err_t protocomm_add_endpoint_internal(protocomm_t *pc, const char *ep_name,
                                                 protocomm_req_handler_t h, void *priv_data,
                                                 uint32_t flag)
{
    if ((pc == NULL) || (ep_name == NULL) || (h == NULL)) {
        return ESP_ERR_INVALID_ARG;
    }

    protocomm_ep_t *ep;
    esp_err_t ret;

    ep = search_endpoint(pc, ep_name);
    if (ep) {
        ESP_LOGE(TAG, "Endpoint with this name already exists");
        return ESP_FAIL;
    }

    if (pc->add_endpoint) {
        ret = pc->add_endpoint(ep_name, h, priv_data);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Error adding endpoint");
            return ret;
        }
    }

    ep = (protocomm_ep_t *) calloc(1, sizeof(protocomm_ep_t));
    if (!ep) {
        ESP_LOGE(TAG, "Error allocating endpoint resource");
        return ESP_ERR_NO_MEM;
    }

    /* Initialize ep handler */
    ep->ep_name = ep_name;
    ep->req_handler = h;
    ep->priv_data = priv_data;
    ep->flag = flag;

    /* Add endpoint to the head of the singly linked list */
    SLIST_INSERT_HEAD(&pc->endpoints, ep, next);

    return ESP_OK;
}