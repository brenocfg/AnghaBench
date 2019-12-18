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
struct TYPE_7__ {int type; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct TYPE_9__ {int max_adj; int /*<<< orphan*/  name; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/ * ptp_clock; TYPE_3__* pdev; TYPE_4__ ptp_clock_info; int /*<<< orphan*/  systim_overflow_work; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SYSTIM_OVERFLOW_PERIOD ; 
 int E1000_TSYNCRXCTL_SYSCFI ; 
 int FLAG_HAS_HW_TIMESTAMP ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSYNCRXCTL ; 
#define  e1000_82574 131 
#define  e1000_82583 130 
#define  e1000_pch2lan 129 
#define  e1000_pch_lpt 128 
 TYPE_4__ e1000e_ptp_clock_info ; 
 int /*<<< orphan*/  e1000e_systim_overflow_work ; 
 int /*<<< orphan*/  e_err (char*) ; 
 int /*<<< orphan*/  e_info (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

void e1000e_ptp_init(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	adapter->ptp_clock = NULL;

	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		return;

	adapter->ptp_clock_info = e1000e_ptp_clock_info;

	snprintf(adapter->ptp_clock_info.name,
		 sizeof(adapter->ptp_clock_info.name), "%pm",
		 adapter->netdev->perm_addr);

	switch (hw->mac.type) {
	case e1000_pch2lan:
	case e1000_pch_lpt:
		if ((hw->mac.type != e1000_pch_lpt) ||
		    (er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_SYSCFI)) {
			adapter->ptp_clock_info.max_adj = 24000000 - 1;
			break;
		}
		/* fall-through */
	case e1000_82574:
	case e1000_82583:
		adapter->ptp_clock_info.max_adj = 600000000 - 1;
		break;
	default:
		break;
	}

	INIT_DELAYED_WORK(&adapter->systim_overflow_work,
			  e1000e_systim_overflow_work);

	schedule_delayed_work(&adapter->systim_overflow_work,
			      E1000_SYSTIM_OVERFLOW_PERIOD);

	adapter->ptp_clock = ptp_clock_register(&adapter->ptp_clock_info,
						&adapter->pdev->dev);
	if (IS_ERR(adapter->ptp_clock)) {
		adapter->ptp_clock = NULL;
		e_err("ptp_clock_register failed\n");
	} else {
		e_info("registered PHC clock\n");
	}
}