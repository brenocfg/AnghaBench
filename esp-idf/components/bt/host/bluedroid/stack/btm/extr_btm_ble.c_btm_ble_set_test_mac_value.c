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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/  test_mac; int /*<<< orphan*/  enable_test_mac_val; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET8_LEN ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btm_ble_set_test_mac_value(BOOLEAN enable, UINT8 *p_test_mac_val )
{
    BTM_TRACE_DEBUG ("btm_ble_set_test_mac_value enable=%d", enable);
    btm_cb.devcb.enable_test_mac_val = enable;
    memcpy(btm_cb.devcb.test_mac, p_test_mac_val, BT_OCTET8_LEN);
}