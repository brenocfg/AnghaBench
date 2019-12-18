#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pop; TYPE_1__* sec; int /*<<< orphan*/ * sec_inst; } ;
typedef  TYPE_2__ protocomm_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocomm_remove_endpoint (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

esp_err_t protocomm_unset_security(protocomm_t *pc, const char *ep_name)
{
    if ((pc == NULL) || (ep_name == NULL)) {
        return ESP_FAIL;
    }

    if (pc->sec && pc->sec->cleanup) {
        pc->sec->cleanup(pc->sec_inst);
        pc->sec_inst = NULL;
        pc->sec = NULL;
    }

    if (pc->pop) {
        free(pc->pop);
        pc->pop = NULL;
    }

    return protocomm_remove_endpoint(pc, ep_name);
}