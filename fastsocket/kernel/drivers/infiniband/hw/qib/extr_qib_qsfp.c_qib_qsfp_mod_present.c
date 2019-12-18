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
typedef  int u32 ;
struct qib_pportdata {int hw_pidx; TYPE_1__* dd; } ;
struct TYPE_2__ {int (* f_gpio_mod ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int QSFP_GPIO_MOD_PRS_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qib_qsfp_mod_present(struct qib_pportdata *ppd)
{
	u32 mask;
	int ret;

	mask = QSFP_GPIO_MOD_PRS_N <<
		(ppd->hw_pidx * QSFP_GPIO_PORT2_SHIFT);
	ret = ppd->dd->f_gpio_mod(ppd->dd, 0, 0, 0);

	return !((ret & mask) >>
		 ((ppd->hw_pidx * QSFP_GPIO_PORT2_SHIFT) + 3));
}