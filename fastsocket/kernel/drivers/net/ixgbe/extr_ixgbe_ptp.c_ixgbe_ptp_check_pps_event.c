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
typedef  int /*<<< orphan*/  u32 ;
struct ptp_clock_event {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  ptp_clock; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTP_CLOCK_PPS ; 
#define  ixgbe_mac_X540 128 
 int /*<<< orphan*/  ptp_clock_event (int /*<<< orphan*/ ,struct ptp_clock_event*) ; 

void ixgbe_ptp_check_pps_event(struct ixgbe_adapter *adapter, u32 eicr)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ptp_clock_event event;

	event.type = PTP_CLOCK_PPS;

	/* this check is necessary in case the interrupt was enabled via some
	 * alternative means (ex. debug_fs). Better to check here than
	 * everywhere that calls this function.
	 */
	if (!adapter->ptp_clock)
		return;

	switch (hw->mac.type) {
	case ixgbe_mac_X540:
		ptp_clock_event(adapter->ptp_clock, &event);
		break;
	default:
		break;
	}
}