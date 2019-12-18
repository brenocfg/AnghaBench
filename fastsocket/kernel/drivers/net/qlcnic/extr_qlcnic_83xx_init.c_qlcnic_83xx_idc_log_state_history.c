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
typedef  size_t u32 ;
struct qlcnic_adapter {TYPE_2__* ahw; TYPE_3__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {size_t curr_state; size_t prev_state; int /*<<< orphan*/ * name; } ;
struct TYPE_5__ {TYPE_1__ idc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_83xx_idc_log_state_history(struct qlcnic_adapter *adapter)
{
	u32 cur, prev;
	cur = adapter->ahw->idc.curr_state;
	prev = adapter->ahw->idc.prev_state;

	dev_info(&adapter->pdev->dev,
		 "current state  = %s,  prev state = %s\n",
		 adapter->ahw->idc.name[cur],
		 adapter->ahw->idc.name[prev]);
}