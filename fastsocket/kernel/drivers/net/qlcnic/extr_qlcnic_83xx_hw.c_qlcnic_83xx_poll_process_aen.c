#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 int QLCNIC_MBX_ASYNC_EVENT ; 
 int /*<<< orphan*/  QLCNIC_MBX_FW (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int QLCNIC_SET_OWNER ; 
 int QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qlcnic_83xx_process_aen (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_legacy_msix_mbx_intr (struct qlcnic_adapter*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qlcnic_83xx_poll_process_aen(struct qlcnic_adapter *adapter)
{
	u32 resp, event;
	unsigned long flags;

	spin_lock_irqsave(&adapter->ahw->mbx_lock, flags);

	resp = QLCRDX(adapter->ahw, QLCNIC_FW_MBX_CTRL);
	if (!(resp & QLCNIC_SET_OWNER))
		goto out;

	event = readl(QLCNIC_MBX_FW(adapter->ahw, 0));
	if (event &  QLCNIC_MBX_ASYNC_EVENT)
		__qlcnic_83xx_process_aen(adapter);

out:
	qlcnic_83xx_enable_legacy_msix_mbx_intr(adapter);
	spin_unlock_irqrestore(&adapter->ahw->mbx_lock, flags);
}