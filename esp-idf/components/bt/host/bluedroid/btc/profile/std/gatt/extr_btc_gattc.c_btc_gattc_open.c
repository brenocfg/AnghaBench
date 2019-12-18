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
typedef  int /*<<< orphan*/  tBTA_GATT_TRANSPORT ;
struct TYPE_4__ {int /*<<< orphan*/  is_direct; int /*<<< orphan*/  remote_addr_type; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  gattc_if; } ;
struct TYPE_5__ {TYPE_1__ open; } ;
typedef  TYPE_2__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_Open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_GATT_TRANSPORT_LE ; 

__attribute__((used)) static void btc_gattc_open(btc_ble_gattc_args_t *arg)
{
    tBTA_GATT_TRANSPORT transport = BTA_GATT_TRANSPORT_LE;
    BTA_GATTC_Open(arg->open.gattc_if, arg->open.remote_bda, arg->open.remote_addr_type, arg->open.is_direct, transport);
}