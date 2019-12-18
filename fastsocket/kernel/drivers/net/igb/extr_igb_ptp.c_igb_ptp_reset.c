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
struct timespec {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int flags; int /*<<< orphan*/  cc; int /*<<< orphan*/  tc; int /*<<< orphan*/  ptp_caps; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_TS ; 
 int /*<<< orphan*/  E1000_TIMINCA ; 
 int /*<<< orphan*/  E1000_TSAUXC ; 
 int /*<<< orphan*/  E1000_TSIM ; 
 int E1000_TSIM_TXTS ; 
 int IGB_FLAG_PTP ; 
 int INCPERIOD_82576 ; 
 int INCVALUE_82576 ; 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 int /*<<< orphan*/  igb_ptp_settime_i210 (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct timespec ktime_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timecounter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

void igb_ptp_reset(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	if (!(adapter->flags & IGB_FLAG_PTP))
		return;

	switch (adapter->hw.mac.type) {
	case e1000_82576:
		/* Dial the nominal frequency. */
		wr32(E1000_TIMINCA, INCPERIOD_82576 | INCVALUE_82576);
		break;
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
	case e1000_i210:
	case e1000_i211:
		/* Enable the timer functions and interrupts. */
		wr32(E1000_TSAUXC, 0x0);
		wr32(E1000_TSIM, E1000_TSIM_TXTS);
		wr32(E1000_IMS, E1000_IMS_TS);
		break;
	default:
		/* No work to do. */
		return;
	}

	/* Re-initialize the timer. */
	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211)) {
		struct timespec ts = ktime_to_timespec(ktime_get_real());

		igb_ptp_settime_i210(&adapter->ptp_caps, &ts);
	} else {
		timecounter_init(&adapter->tc, &adapter->cc,
				 ktime_to_ns(ktime_get_real()));
	}
}