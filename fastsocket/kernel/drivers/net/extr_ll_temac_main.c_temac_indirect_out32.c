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
struct temac_local {int dummy; } ;

/* Variables and functions */
 int CNTLREG_WRITE_ENABLE_MASK ; 
 int /*<<< orphan*/  XTE_CTL0_OFFSET ; 
 int /*<<< orphan*/  XTE_LSW0_OFFSET ; 
 scalar_t__ temac_indirect_busywait (struct temac_local*) ; 
 int /*<<< orphan*/  temac_iow (struct temac_local*,int /*<<< orphan*/ ,int) ; 

void temac_indirect_out32(struct temac_local *lp, int reg, u32 value)
{
	if (temac_indirect_busywait(lp))
		return;
	temac_iow(lp, XTE_LSW0_OFFSET, value);
	temac_iow(lp, XTE_CTL0_OFFSET, CNTLREG_WRITE_ENABLE_MASK | reg);
}