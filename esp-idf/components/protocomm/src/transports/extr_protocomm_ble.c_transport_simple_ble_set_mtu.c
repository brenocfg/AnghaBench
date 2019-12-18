#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_gatts_cb_event_t ;
typedef  int /*<<< orphan*/  esp_gatt_if_t ;
struct TYPE_5__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_6__ {TYPE_1__ mtu; } ;
typedef  TYPE_2__ esp_ble_gatts_cb_param_t ;
struct TYPE_7__ {int /*<<< orphan*/  gatt_mtu; } ;

/* Variables and functions */
 TYPE_4__* protoble_internal ; 

__attribute__((used)) static void transport_simple_ble_set_mtu(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param)
{
    protoble_internal->gatt_mtu = param->mtu.mtu;
    return;
}