#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_BLE_CONN_ST ;
struct TYPE_3__ {int /*<<< orphan*/  conn_state; } ;
struct TYPE_4__ {TYPE_1__ ble_ctr_cb; } ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 

tBTM_BLE_CONN_ST btm_ble_get_conn_st(void)
{
    return btm_cb.ble_ctr_cb.conn_state;
}