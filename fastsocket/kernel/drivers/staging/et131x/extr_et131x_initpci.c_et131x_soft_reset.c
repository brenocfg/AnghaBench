#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct et131x_adapter {TYPE_2__* regs; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {TYPE_3__ cfg1; } ;
struct TYPE_5__ {int /*<<< orphan*/  sw_reset; } ;
struct TYPE_6__ {TYPE_4__ mac; TYPE_1__ global; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void et131x_soft_reset(struct et131x_adapter *adapter)
{
	/* Disable MAC Core */
	writel(0xc00f0000, &adapter->regs->mac.cfg1.value);

	/* Set everything to a reset value */
	writel(0x7F, &adapter->regs->global.sw_reset);
	writel(0x000f0000, &adapter->regs->mac.cfg1.value);
	writel(0x00000000, &adapter->regs->mac.cfg1.value);
}