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
struct TYPE_7__ {int /*<<< orphan*/  handles; int /*<<< orphan*/  num_attr; } ;
typedef  TYPE_2__ tBTA_GATTC_MULTI ;
struct TYPE_6__ {int /*<<< orphan*/  auth_req; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  handles; int /*<<< orphan*/  num_attr; } ;
struct TYPE_8__ {TYPE_1__ read_multiple; } ;
typedef  TYPE_3__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_MULTI_MAX ; 
 int /*<<< orphan*/  BTA_GATTC_ReadMultiple (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gattc_read_multiple_char(btc_ble_gattc_args_t *arg)
{
    tBTA_GATTC_MULTI bta_multi;
    bta_multi.num_attr = arg->read_multiple.num_attr;
    memcpy(bta_multi.handles, arg->read_multiple.handles, BTA_GATTC_MULTI_MAX);
    BTA_GATTC_ReadMultiple(arg->read_multiple.conn_id, &bta_multi, arg->read_multiple.auth_req);
}