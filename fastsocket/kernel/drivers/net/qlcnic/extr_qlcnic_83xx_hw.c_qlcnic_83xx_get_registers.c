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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int QLCNIC_DEV_INFO_SIZE ; 
 int /*<<< orphan*/  QLCRDX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_ext_reg_tbl ; 
 int /*<<< orphan*/  qlcnic_83xx_reg_tbl ; 

int qlcnic_83xx_get_registers(struct qlcnic_adapter *adapter, u32 *regs_buff)
{
	int i, j = 0;

	for (i = QLCNIC_DEV_INFO_SIZE + 1;
	     j < ARRAY_SIZE(qlcnic_83xx_reg_tbl); i++, j++)
		regs_buff[i] = QLC_SHARED_REG_RD32(adapter, j);

	for (j = 0; j < ARRAY_SIZE(qlcnic_83xx_ext_reg_tbl); j++)
		regs_buff[i++] = QLCRDX(adapter->ahw, j);
	return i;
}