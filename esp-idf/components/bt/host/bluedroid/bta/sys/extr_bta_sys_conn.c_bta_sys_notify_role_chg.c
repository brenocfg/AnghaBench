#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_role_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  BD_ADDR_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_SYS_ROLE_CHANGE ; 
 TYPE_1__ bta_sys_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_sys_notify_role_chg(BD_ADDR_PTR p_bda, UINT8 new_role, UINT8 hci_status)
{
    if (bta_sys_cb.p_role_cb) {
        bta_sys_cb.p_role_cb(BTA_SYS_ROLE_CHANGE, new_role, hci_status, p_bda);
    }
}