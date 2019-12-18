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
struct TYPE_7__ {int /*<<< orphan*/  p_value; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ tBTA_GATT_UNFMT ;
struct TYPE_6__ {int /*<<< orphan*/  auth_req; int /*<<< orphan*/  write_type; int /*<<< orphan*/  handle; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  value; int /*<<< orphan*/  value_len; } ;
struct TYPE_8__ {TYPE_1__ write_descr; } ;
typedef  TYPE_3__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_WriteCharDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gattc_write_char_descr(btc_ble_gattc_args_t *arg)
{
    tBTA_GATT_UNFMT descr_val;

    descr_val.len = arg->write_descr.value_len;
    descr_val.p_value = arg->write_descr.value;

    BTA_GATTC_WriteCharDescr(arg->write_descr.conn_id,
                             arg->write_descr.handle,
                             arg->write_descr.write_type, &descr_val,
                             arg->write_descr.auth_req);
}