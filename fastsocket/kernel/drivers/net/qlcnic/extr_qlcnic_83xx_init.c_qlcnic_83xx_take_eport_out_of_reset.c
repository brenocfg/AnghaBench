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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QLC_83XX_RESET_CONTROL ; 
 int /*<<< orphan*/  QLC_83XX_RESET_EPGSHIM ; 
 int /*<<< orphan*/  QLC_83XX_RESET_ETHERPCS ; 
 int /*<<< orphan*/  QLC_83XX_RESET_PORT0 ; 
 int /*<<< orphan*/  QLC_83XX_RESET_PORT1 ; 
 int /*<<< orphan*/  QLC_83XX_RESET_PORT2 ; 
 int /*<<< orphan*/  QLC_83XX_RESET_PORT3 ; 
 int /*<<< orphan*/  QLC_83XX_RESET_REG ; 
 int /*<<< orphan*/  QLC_83XX_RESET_SRESHIM ; 

__attribute__((used)) static void qlcnic_83xx_take_eport_out_of_reset(struct qlcnic_adapter *adapter)
{
	QLCWR32(adapter, QLC_83XX_RESET_REG, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT0, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT1, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT2, 0);
	QLCWR32(adapter, QLC_83XX_RESET_PORT3, 0);
	QLCWR32(adapter, QLC_83XX_RESET_SRESHIM, 0);
	QLCWR32(adapter, QLC_83XX_RESET_EPGSHIM, 0);
	QLCWR32(adapter, QLC_83XX_RESET_ETHERPCS, 0);
	QLCWR32(adapter, QLC_83XX_RESET_CONTROL, 1);
}