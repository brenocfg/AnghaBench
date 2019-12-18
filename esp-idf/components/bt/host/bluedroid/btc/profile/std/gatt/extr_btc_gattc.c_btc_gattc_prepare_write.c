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
struct TYPE_4__ {int /*<<< orphan*/  auth_req; int /*<<< orphan*/  value; int /*<<< orphan*/  value_len; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  conn_id; } ;
struct TYPE_5__ {TYPE_1__ prep_write; } ;
typedef  TYPE_2__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_PrepareWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gattc_prepare_write(btc_ble_gattc_args_t *arg)
{
    BTA_GATTC_PrepareWrite(arg->prep_write.conn_id,
                           arg->prep_write.handle,
                           arg->prep_write.offset,
                           arg->prep_write.value_len,
                           arg->prep_write.value,
                           arg->prep_write.auth_req);
}