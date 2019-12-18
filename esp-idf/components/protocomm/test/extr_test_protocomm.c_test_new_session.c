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
struct TYPE_4__ {scalar_t__ sec_ver; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_5__ {scalar_t__ (* init ) (int /*<<< orphan*/ *) ;scalar_t__ (* new_transport_session ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ protocomm_open_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_inst ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_pc ; 
 TYPE_2__* test_sec ; 

__attribute__((used)) static esp_err_t test_new_session(session_t *session)
{
    if (session->sec_ver == 0) {
        return ESP_OK;
    }

    if (!test_sec) {
        return ESP_ERR_INVALID_STATE;
    }

    if (test_sec->init && (test_sec->init(&sec_inst) != ESP_OK)) {
        return ESP_ERR_NO_MEM;
    }

    uint32_t session_id = session->id;
    if (test_sec->new_transport_session &&
        (test_sec->new_transport_session(sec_inst, session_id) != ESP_OK)) {
        ESP_LOGE(TAG, "Failed to launch new transport session");
        return ESP_FAIL;
    }

    if (protocomm_open_session(test_pc, session_id) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open new protocomm session");
        return ESP_FAIL;
    }
    return ESP_OK;
}