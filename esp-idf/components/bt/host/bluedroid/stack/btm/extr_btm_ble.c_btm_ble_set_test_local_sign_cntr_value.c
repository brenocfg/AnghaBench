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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {int /*<<< orphan*/  test_local_sign_cntr; int /*<<< orphan*/  enable_test_local_sign_cntr; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 

void btm_ble_set_test_local_sign_cntr_value(BOOLEAN enable, UINT32 test_local_sign_cntr )
{
    BTM_TRACE_DEBUG ("btm_ble_set_test_local_sign_cntr_value enable=%d local_sign_cntr=%d",
                     enable, test_local_sign_cntr);
    btm_cb.devcb.enable_test_local_sign_cntr = enable;
    btm_cb.devcb.test_local_sign_cntr =  test_local_sign_cntr;
}