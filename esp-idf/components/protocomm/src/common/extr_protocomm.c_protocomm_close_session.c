#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  sec_inst; TYPE_1__* sec; } ;
typedef  TYPE_2__ protocomm_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_4__ {scalar_t__ (* close_transport_session ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t protocomm_close_session(protocomm_t *pc, uint32_t session_id)
{
    if (!pc) {
        return ESP_ERR_INVALID_ARG;
    }

    if (pc->sec && pc->sec->close_transport_session) {
        esp_err_t ret = pc->sec->close_transport_session(pc->sec_inst, session_id);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Error while closing session with ID: %d", session_id);
            return ret;
        }
    }
    return ESP_OK;
}