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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_RGMII_IMP ; 
 int F_CALRESET ; 
 int F_CALUPDATE ; 
 int F_XGM_IMPSETUPDATE ; 
 int V_RGMIIIMPPD (int) ; 
 int V_RGMIIIMPPU (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uses_xaui (struct adapter*) ; 

__attribute__((used)) static void calibrate_xgm_t3b(struct adapter *adapter)
{
	if (!uses_xaui(adapter)) {
		t3_write_reg(adapter, A_XGM_RGMII_IMP, F_CALRESET |
			     F_CALUPDATE | V_RGMIIIMPPD(2) | V_RGMIIIMPPU(3));
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_CALRESET, 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, 0,
				 F_XGM_IMPSETUPDATE);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_XGM_IMPSETUPDATE,
				 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_CALUPDATE, 0);
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, 0, F_CALUPDATE);
	}
}