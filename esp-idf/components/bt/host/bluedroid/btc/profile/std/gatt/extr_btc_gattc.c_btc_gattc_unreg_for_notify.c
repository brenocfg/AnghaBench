#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATT_STATUS ;
struct TYPE_8__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_1__ unreg_for_notify; } ;
typedef  TYPE_3__ esp_ble_gattc_cb_param_t ;
struct TYPE_9__ {int /*<<< orphan*/  gattc_if; int /*<<< orphan*/  handle; int /*<<< orphan*/  remote_bda; } ;
struct TYPE_11__ {TYPE_2__ unreg_for_notify; } ;
typedef  TYPE_4__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_DeregisterForNotifications (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_GATTC_UNREG_FOR_NOTIFY_EVT ; 
 int /*<<< orphan*/  btc_gattc_cb_to_app (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void btc_gattc_unreg_for_notify(btc_ble_gattc_args_t *arg)
{
    tBTA_GATT_STATUS status;
    esp_ble_gattc_cb_param_t param;

    status = BTA_GATTC_DeregisterForNotifications(arg->unreg_for_notify.gattc_if,
             arg->unreg_for_notify.remote_bda,
             arg->unreg_for_notify.handle);

    memset(&param, 0, sizeof(esp_ble_gattc_cb_param_t));
    param.unreg_for_notify.status = status;
    param.unreg_for_notify.handle = arg->unreg_for_notify.handle;
    btc_gattc_cb_to_app(ESP_GATTC_UNREG_FOR_NOTIFY_EVT, arg->unreg_for_notify.gattc_if, &param);
}