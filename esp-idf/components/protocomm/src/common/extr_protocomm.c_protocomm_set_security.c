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
struct TYPE_7__ {int /*<<< orphan*/ * pop; TYPE_2__ const* sec; int /*<<< orphan*/ * sec_inst; } ;
typedef  TYPE_1__ protocomm_t ;
struct TYPE_8__ {scalar_t__ (* init ) (int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ protocomm_security_t ;
typedef  int /*<<< orphan*/  protocomm_security_pop_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  SEC_EP ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ protocomm_add_endpoint_internal (TYPE_1__*,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  protocomm_common_security_handler ; 
 int /*<<< orphan*/  protocomm_remove_endpoint (TYPE_1__*,char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

esp_err_t protocomm_set_security(protocomm_t *pc, const char *ep_name,
                                 const protocomm_security_t *sec,
                                 const protocomm_security_pop_t *pop)
{
    if ((pc == NULL) || (ep_name == NULL) || (sec == NULL)) {
        return ESP_ERR_INVALID_ARG;
    }

    if (pc->sec) {
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = protocomm_add_endpoint_internal(pc, ep_name,
                                                    protocomm_common_security_handler,
                                                    (void *) pc, SEC_EP);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Error adding security endpoint");
        return ret;
    }

    if (sec->init) {
        ret = sec->init(&pc->sec_inst);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Error initializing security");
            protocomm_remove_endpoint(pc, ep_name);
            return ret;
        }
    }
    pc->sec = sec;

    if (pop) {
        pc->pop = malloc(sizeof(protocomm_security_pop_t));
        if (pc->pop == NULL) {
            ESP_LOGE(TAG, "Error allocating Proof of Possession");
            if (pc->sec && pc->sec->cleanup) {
                pc->sec->cleanup(pc->sec_inst);
                pc->sec_inst = NULL;
                pc->sec = NULL;
            }

            protocomm_remove_endpoint(pc, ep_name);
            return ESP_ERR_NO_MEM;
        }
        memcpy((void *)pc->pop, pop, sizeof(protocomm_security_pop_t));
    }
    return ESP_OK;
}