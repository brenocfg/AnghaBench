#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qlcnic_adapter {int /*<<< orphan*/  mbx_poll_work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_MBX_POLL_ENABLE ; 
 int /*<<< orphan*/  qlcnic_83xx_mbx_poll_work ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_83xx_enable_mbx_poll(struct qlcnic_adapter *adapter)
{
	if (test_and_set_bit(__QLCNIC_MBX_POLL_ENABLE, &adapter->state))
		return;

	INIT_DELAYED_WORK(&adapter->mbx_poll_work, qlcnic_83xx_mbx_poll_work);
}