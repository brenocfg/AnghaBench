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
struct adapter {int swintr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int PFSW ; 
 int /*<<< orphan*/  PL_PF_INT_CAUSE ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_slow_intr_handler (struct adapter*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t t4_nondata_intr(int irq, void *cookie)
{
	struct adapter *adap = cookie;

	u32 v = t4_read_reg(adap, MYPF_REG(PL_PF_INT_CAUSE));
	if (v & PFSW) {
		adap->swintr = 1;
		t4_write_reg(adap, MYPF_REG(PL_PF_INT_CAUSE), v);
	}
	t4_slow_intr_handler(adap);
	return IRQ_HANDLED;
}