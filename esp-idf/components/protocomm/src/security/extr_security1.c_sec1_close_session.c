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
struct TYPE_3__ {int id; scalar_t__ state; int /*<<< orphan*/  ctx_aes; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ protocomm_security_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ SESSION_STATE_DONE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  mbedtls_aes_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t sec1_close_session(protocomm_security_handle_t handle, uint32_t session_id)
{
    session_t *cur_session = (session_t *) handle;
    if (!cur_session) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!cur_session || cur_session->id != session_id) {
        ESP_LOGE(TAG, "Attempt to close invalid session");
        return ESP_ERR_INVALID_STATE;
    }

    if (cur_session->state == SESSION_STATE_DONE) {
        /* Free AES context data */
        mbedtls_aes_free(&cur_session->ctx_aes);
    }

    memset(cur_session, 0, sizeof(session_t));
    cur_session->id = -1;
    return ESP_OK;
}