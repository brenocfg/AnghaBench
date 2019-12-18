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
typedef  int uint32_t ;
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ protocomm_security_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  sec1_close_session (TYPE_1__*,int) ; 

__attribute__((used)) static esp_err_t sec1_new_session(protocomm_security_handle_t handle, uint32_t session_id)
{
    session_t *cur_session = (session_t *) handle;
    if (!cur_session) {
        return ESP_ERR_INVALID_ARG;
    }

    if (cur_session->id != -1) {
        /* Only one session is allowed at a time */
        ESP_LOGE(TAG, "Closing old session with id %u", cur_session->id);
        sec1_close_session(cur_session, session_id);
    }

    cur_session->id = session_id;
    return ESP_OK;
}