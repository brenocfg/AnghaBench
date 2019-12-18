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
struct TYPE_5__ {scalar_t__ (* send_cmd ) (TYPE_1__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ modem_dte_t ;
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  handle_line; TYPE_1__* dte; } ;
typedef  TYPE_2__ modem_dce_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCE_TAG ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MODEM_COMMAND_TIMEOUT_DEFAULT ; 
 scalar_t__ MODEM_STATE_SUCCESS ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  esp_modem_dce_handle_response_default ; 
 scalar_t__ stub1 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

esp_err_t esp_modem_dce_sync(modem_dce_t *dce)
{
    modem_dte_t *dte = dce->dte;
    dce->handle_line = esp_modem_dce_handle_response_default;
    DCE_CHECK(dte->send_cmd(dte, "AT\r", MODEM_COMMAND_TIMEOUT_DEFAULT) == ESP_OK, "send command failed", err);
    DCE_CHECK(dce->state == MODEM_STATE_SUCCESS, "sync failed", err);
    ESP_LOGD(DCE_TAG, "sync ok");
    return ESP_OK;
err:
    return ESP_FAIL;
}