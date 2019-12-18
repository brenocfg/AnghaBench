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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_base0; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_rd_reg_indirect (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_read_window_reg (int,int /*<<< orphan*/ ,int*) ; 

int qlcnic_ind_rd(struct qlcnic_adapter *adapter, u32 addr)
{
	u32 data;

	if (qlcnic_82xx_check(adapter))
		qlcnic_read_window_reg(addr, adapter->ahw->pci_base0, &data);
	else {
		data = qlcnic_83xx_rd_reg_indirect(adapter, addr);
		if (data == -EIO)
			return -EIO;
	}
	return data;
}