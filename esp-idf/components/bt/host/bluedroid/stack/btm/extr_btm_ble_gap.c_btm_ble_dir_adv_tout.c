#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  directed_conn; int /*<<< orphan*/  adv_mode; } ;
struct TYPE_5__ {TYPE_1__ inq_var; } ;
struct TYPE_6__ {TYPE_2__ ble_ctr_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_ADV_DISABLE ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__ btm_cb ; 

void btm_ble_dir_adv_tout(void)
{
    btm_cb.ble_ctr_cb.inq_var.adv_mode = BTM_BLE_ADV_DISABLE;

    /* make device fall back into undirected adv mode by default */
    btm_cb.ble_ctr_cb.inq_var.directed_conn = FALSE;
}