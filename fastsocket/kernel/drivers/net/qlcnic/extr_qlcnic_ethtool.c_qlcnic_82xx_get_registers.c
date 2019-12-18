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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int QLCNIC_DEV_INFO_SIZE ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int) ; 
 int* diag_registers ; 
 int* ext_diag_registers ; 

__attribute__((used)) static int qlcnic_82xx_get_registers(struct qlcnic_adapter *adapter,
				     u32 *regs_buff)
{
	int i, j = 0;

	for (i = QLCNIC_DEV_INFO_SIZE + 1; diag_registers[j] != -1; j++, i++)
		regs_buff[i] = QLC_SHARED_REG_RD32(adapter, diag_registers[j]);
	j = 0;
	while (ext_diag_registers[j] != -1)
		regs_buff[i++] = QLCRD32(adapter, ext_diag_registers[j++]);
	return i;
}