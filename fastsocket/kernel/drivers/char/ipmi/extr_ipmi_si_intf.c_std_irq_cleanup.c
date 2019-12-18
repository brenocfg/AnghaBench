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
struct TYPE_2__ {int /*<<< orphan*/  (* outputb ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct smi_info {scalar_t__ si_type; int /*<<< orphan*/  irq; TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_BT_INTMASK_REG ; 
 scalar_t__ SI_BT ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct smi_info*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void std_irq_cleanup(struct smi_info *info)
{
	if (info->si_type == SI_BT)
		/* Disable the interrupt in the BT interface. */
		info->io.outputb(&info->io, IPMI_BT_INTMASK_REG, 0);
	free_irq(info->irq, info);
}