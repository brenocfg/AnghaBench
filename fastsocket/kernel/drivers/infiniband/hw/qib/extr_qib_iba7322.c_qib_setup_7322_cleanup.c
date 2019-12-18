#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qib_devdata {int num_pports; int flags; TYPE_5__* pport; TYPE_1__* cspec; } ;
struct TYPE_9__ {TYPE_3__* smi_ah; } ;
struct TYPE_10__ {TYPE_4__ ibport_data; TYPE_2__* cpspec; } ;
struct TYPE_8__ {int /*<<< orphan*/  ibah; } ;
struct TYPE_7__ {int /*<<< orphan*/  qsfp_data; int /*<<< orphan*/  portcntrs; } ;
struct TYPE_6__ {int gpio_mask; int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  msix_entries; int /*<<< orphan*/  sendibchk; int /*<<< orphan*/  sendgrhchk; int /*<<< orphan*/  sendchkenable; int /*<<< orphan*/  cntrs; } ;

/* Variables and functions */
 int QIB_HAS_QSFP ; 
 int QSFP_GPIO_MOD_PRS_N ; 
 int QSFP_GPIO_PORT2_SHIFT ; 
 int /*<<< orphan*/  ib_destroy_ah (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_gpio_mask ; 
 int /*<<< orphan*/  qib_7322_free_irq (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_qsfp_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_setup_7322_cleanup(struct qib_devdata *dd)
{
	int i;

	qib_7322_free_irq(dd);
	kfree(dd->cspec->cntrs);
	kfree(dd->cspec->sendchkenable);
	kfree(dd->cspec->sendgrhchk);
	kfree(dd->cspec->sendibchk);
	kfree(dd->cspec->msix_entries);
	for (i = 0; i < dd->num_pports; i++) {
		unsigned long flags;
		u32 mask = QSFP_GPIO_MOD_PRS_N |
			(QSFP_GPIO_MOD_PRS_N << QSFP_GPIO_PORT2_SHIFT);

		kfree(dd->pport[i].cpspec->portcntrs);
		if (dd->flags & QIB_HAS_QSFP) {
			spin_lock_irqsave(&dd->cspec->gpio_lock, flags);
			dd->cspec->gpio_mask &= ~mask;
			qib_write_kreg(dd, kr_gpio_mask, dd->cspec->gpio_mask);
			spin_unlock_irqrestore(&dd->cspec->gpio_lock, flags);
			qib_qsfp_deinit(&dd->pport[i].cpspec->qsfp_data);
		}
		if (dd->pport[i].ibport_data.smi_ah)
			ib_destroy_ah(&dd->pport[i].ibport_data.smi_ah->ibah);
	}
}