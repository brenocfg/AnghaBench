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
typedef  int /*<<< orphan*/  esp_blufi_error_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_1__ report_error; } ;
typedef  TYPE_2__ esp_blufi_cb_param_t ;
struct TYPE_8__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_3__ btc_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PID_BLUFI ; 
 int /*<<< orphan*/  BTC_SIG_API_CB ; 
 int /*<<< orphan*/  ESP_BLUFI_EVENT_REPORT_ERROR ; 
 int /*<<< orphan*/  btc_transfer_context (TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 

void btc_blufi_report_error(esp_blufi_error_state_t state)
{
    btc_msg_t msg;
    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_BLUFI;
    msg.act = ESP_BLUFI_EVENT_REPORT_ERROR;
    esp_blufi_cb_param_t param;
    param.report_error.state = state;
    btc_transfer_context(&msg, &param, sizeof(esp_blufi_cb_param_t), NULL);
}