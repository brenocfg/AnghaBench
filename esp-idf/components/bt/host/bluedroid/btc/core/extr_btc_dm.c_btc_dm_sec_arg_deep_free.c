#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ act; scalar_t__ arg; } ;
typedef  TYPE_3__ btc_msg_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_key_value; } ;
struct TYPE_7__ {TYPE_1__ ble_key; } ;
struct TYPE_9__ {TYPE_2__ sec; } ;
typedef  TYPE_4__ btc_dm_sec_args_t ;

/* Variables and functions */
 scalar_t__ BTA_DM_BLE_KEY_EVT ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_dm_sec_arg_deep_free(btc_msg_t *msg)
{
    btc_dm_sec_args_t *arg = (btc_dm_sec_args_t *)(msg->arg);
    if (msg->act == BTA_DM_BLE_KEY_EVT) {
        osi_free(arg->sec.ble_key.p_key_value);
    }
}