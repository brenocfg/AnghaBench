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
typedef  int u32 ;
struct qlcnic_hardware_context {int /*<<< orphan*/  mbx_lock; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 int QLCNIC_MBX_ASYNC_EVENT ; 
 int /*<<< orphan*/  QLCNIC_MBX_FW (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int QLCNIC_SET_OWNER ; 
 int QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __qlcnic_83xx_process_aen (struct qlcnic_adapter*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qlcnic_83xx_process_aen(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 resp, event;
	unsigned long flags;

	spin_lock_irqsave(&ahw->mbx_lock, flags);

	resp = QLCRDX(ahw, QLCNIC_FW_MBX_CTRL);
	if (resp & QLCNIC_SET_OWNER) {
		event = readl(QLCNIC_MBX_FW(ahw, 0));
		if (event &  QLCNIC_MBX_ASYNC_EVENT)
			__qlcnic_83xx_process_aen(adapter);
	}

	spin_unlock_irqrestore(&ahw->mbx_lock, flags);
}