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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INT_MAP0 ; 
 int /*<<< orphan*/  PL_PF_INT_ENABLE ; 
 int /*<<< orphan*/  PL_WHOAMI ; 
 int SOURCEPF_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t4_intr_disable(struct adapter *adapter)
{
	u32 pf = SOURCEPF_GET(t4_read_reg(adapter, PL_WHOAMI));

	t4_write_reg(adapter, MYPF_REG(PL_PF_INT_ENABLE), 0);
	t4_set_reg_field(adapter, PL_INT_MAP0, 1 << pf, 0);
}