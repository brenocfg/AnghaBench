#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; int /*<<< orphan*/  handle_line; TYPE_3__* dte; } ;
struct TYPE_7__ {TYPE_1__ parent; } ;
typedef  TYPE_2__ sim800_modem_dce_t ;
struct TYPE_8__ {scalar_t__ (* send_cmd ) (TYPE_3__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ modem_dte_t ;
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
 int /*<<< orphan*/  sim800_handle_cgmm ; 
 scalar_t__ stub1 (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t sim800_get_module_name(sim800_modem_dce_t *sim800_dce)
{
    modem_dte_t *dte = sim800_dce->parent.dte;
    sim800_dce->parent.handle_line = sim800_handle_cgmm;
    DCE_CHECK(dte->send_cmd(dte, "AT+CGMM\r", MODEM_COMMAND_TIMEOUT_DEFAULT) == ESP_OK, "send command failed", err);
    DCE_CHECK(sim800_dce->parent.state == MODEM_STATE_SUCCESS, "get module name failed", err);
    ESP_LOGD(DCE_TAG, "get module name ok");
    return ESP_OK;
err:
    return ESP_FAIL;
}