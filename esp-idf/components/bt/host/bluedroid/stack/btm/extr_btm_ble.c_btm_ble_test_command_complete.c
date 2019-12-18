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
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_le_test_cmd_cmpl_cb ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void btm_ble_test_command_complete(UINT8 *p)
{
    tBTM_CMPL_CB   *p_cb = btm_cb.devcb.p_le_test_cmd_cmpl_cb;

    btm_cb.devcb.p_le_test_cmd_cmpl_cb = NULL;

    if (p_cb) {
        (*p_cb)(p);
    }
}