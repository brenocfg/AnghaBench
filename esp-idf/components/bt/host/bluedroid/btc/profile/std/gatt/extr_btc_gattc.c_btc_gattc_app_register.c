#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_9__ {int len; TYPE_1__ uu; } ;
typedef  TYPE_3__ tBT_UUID ;
struct TYPE_8__ {int /*<<< orphan*/  app_id; } ;
struct TYPE_10__ {TYPE_2__ app_reg; } ;
typedef  TYPE_4__ btc_ble_gattc_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_AppRegister (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_gattc_cback ; 

__attribute__((used)) static void btc_gattc_app_register(btc_ble_gattc_args_t *arg)
{
    tBT_UUID app_uuid;
    app_uuid.len = 2;
    app_uuid.uu.uuid16 = arg->app_reg.app_id;
    BTA_GATTC_AppRegister(&app_uuid, btc_gattc_cback);
}