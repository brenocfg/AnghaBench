#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct qib_qsfp_data {struct qib_pportdata* ppd; } ;
struct qib_pportdata {int hw_pidx; struct qib_devdata* dd; TYPE_1__* cpspec; } ;
struct qib_devdata {TYPE_2__* cspec; } ;
struct TYPE_4__ {int extctrl; int gpio_mask; int /*<<< orphan*/  gpio_lock; } ;
struct TYPE_3__ {struct qib_qsfp_data qsfp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCtrl ; 
 int /*<<< orphan*/  GPIOInvert ; 
 int QSFP_GPIO_MOD_PRS_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int SYM_LSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_extctrl ; 
 int /*<<< orphan*/  kr_gpio_mask ; 
 int /*<<< orphan*/  qib_qsfp_init (struct qib_qsfp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsfp_7322_event ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_init_7322_qsfp(struct qib_pportdata *ppd)
{
	unsigned long flags;
	struct qib_qsfp_data *qd = &ppd->cpspec->qsfp_data;
	struct qib_devdata *dd = ppd->dd;
	u64 mod_prs_bit = QSFP_GPIO_MOD_PRS_N;

	mod_prs_bit <<= (QSFP_GPIO_PORT2_SHIFT * ppd->hw_pidx);
	qd->ppd = ppd;
	qib_qsfp_init(qd, qsfp_7322_event);
	spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
	dd->cspec->extctrl |= (mod_prs_bit << SYM_LSB(EXTCtrl, GPIOInvert));
	dd->cspec->gpio_mask |= mod_prs_bit;
	qib_write_kreg(dd, kr_extctrl, dd->cspec->extctrl);
	qib_write_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
	spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
}