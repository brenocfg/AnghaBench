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
struct sgiseeq_regs {int rstat; } ;
struct sgiseeq_private {int mode; } ;
struct hpc3_ethregs {int /*<<< orphan*/  rx_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPC3_ERXCTRL_ACTIVE ; 
 int RSTAT_GO_BITS ; 

__attribute__((used)) static inline void seeq_go(struct sgiseeq_private *sp,
			   struct hpc3_ethregs *hregs,
			   struct sgiseeq_regs *sregs)
{
	sregs->rstat = sp->mode | RSTAT_GO_BITS;
	hregs->rx_ctrl = HPC3_ERXCTRL_ACTIVE;
}