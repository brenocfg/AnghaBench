#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int modem_mode_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* send_cmd ) (TYPE_1__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ modem_dte_t ;
struct TYPE_7__ {int mode; int /*<<< orphan*/  state; int /*<<< orphan*/  handle_line; TYPE_1__* dte; } ;
typedef  TYPE_2__ modem_dce_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCE_TAG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
#define  MODEM_COMMAND_MODE 129 
 int /*<<< orphan*/  MODEM_COMMAND_TIMEOUT_MODE_CHANGE ; 
#define  MODEM_PPP_MODE 128 
 int /*<<< orphan*/  MODEM_STATE_SUCCESS ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  sim800_handle_atd_ppp ; 
 int /*<<< orphan*/  sim800_handle_exit_data_mode ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t sim800_set_working_mode(modem_dce_t *dce, modem_mode_t mode)
{
    modem_dte_t *dte = dce->dte;
    switch (mode) {
    case MODEM_COMMAND_MODE:
        dce->handle_line = sim800_handle_exit_data_mode;
        DCE_CHECK(dte->send_cmd(dte, "+++", MODEM_COMMAND_TIMEOUT_MODE_CHANGE) == ESP_OK, "send command failed", err);
        DCE_CHECK(dce->state == MODEM_STATE_SUCCESS, "enter command mode failed", err);
        ESP_LOGD(DCE_TAG, "enter command mode ok");
        dce->mode = MODEM_COMMAND_MODE;
        break;
    case MODEM_PPP_MODE:
        dce->handle_line = sim800_handle_atd_ppp;
        DCE_CHECK(dte->send_cmd(dte, "ATD*99#\r", MODEM_COMMAND_TIMEOUT_MODE_CHANGE) == ESP_OK, "send command failed", err);
        DCE_CHECK(dce->state == MODEM_STATE_SUCCESS, "enter ppp mode failed", err);
        ESP_LOGD(DCE_TAG, "enter ppp mode ok");
        dce->mode = MODEM_PPP_MODE;
        break;
    default:
        ESP_LOGW(DCE_TAG, "unsupported working mode: %d", mode);
        goto err;
        break;
    }
    return ESP_OK;
err:
    return ESP_FAIL;
}