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
struct qib_qsfp_data {TYPE_1__* ppd; int /*<<< orphan*/  work; } ;
struct qib_devdata {int /*<<< orphan*/  (* f_gpio_mod ) (struct qib_devdata*,int,int,int) ;} ;
struct TYPE_2__ {scalar_t__ hw_pidx; struct qib_devdata* dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int QSFP_GPIO_LP_MODE ; 
 int QSFP_GPIO_MOD_RST_N ; 
 int QSFP_GPIO_MOD_SEL_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct qib_devdata*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void qib_qsfp_init(struct qib_qsfp_data *qd,
		   void (*fevent)(struct work_struct *))
{
	u32 mask, highs;

	struct qib_devdata *dd = qd->ppd->dd;

	/* Initialize work struct for later QSFP events */
	INIT_WORK(&qd->work, fevent);

	/*
	 * Later, we may want more validation. For now, just set up pins and
	 * blip reset. If module is present, call qib_refresh_qsfp_cache(),
	 * to do further init.
	 */
	mask = QSFP_GPIO_MOD_SEL_N | QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	highs = mask - QSFP_GPIO_MOD_RST_N;
	if (qd->ppd->hw_pidx) {
		mask <<= QSFP_GPIO_PORT2_SHIFT;
		highs <<= QSFP_GPIO_PORT2_SHIFT;
	}
	dd->f_gpio_mod(dd, highs, mask, mask);
	udelay(20); /* Generous RST dwell */

	dd->f_gpio_mod(dd, mask, mask, mask);
	return;
}