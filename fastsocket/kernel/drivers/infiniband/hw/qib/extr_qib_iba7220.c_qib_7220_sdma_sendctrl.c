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
typedef  int /*<<< orphan*/  u64 ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {int /*<<< orphan*/  sendctrl_lock; int /*<<< orphan*/  sendctrl; } ;

/* Variables and functions */
 unsigned int QIB_SDMA_SENDCTRL_OP_ENABLE ; 
 unsigned int QIB_SDMA_SENDCTRL_OP_HALT ; 
 unsigned int QIB_SDMA_SENDCTRL_OP_INTENABLE ; 
 int /*<<< orphan*/  SDmaEnable ; 
 int /*<<< orphan*/  SDmaHalt ; 
 int /*<<< orphan*/  SDmaIntEnable ; 
 int /*<<< orphan*/  SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendCtrl ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  kr_sendctrl ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qib_7220_sdma_sendctrl(struct qib_pportdata *ppd, unsigned op)
{
	struct qib_devdata *dd = ppd->dd;
	u64 set_sendctrl = 0;
	u64 clr_sendctrl = 0;

	if (op & QIB_SDMA_SENDCTRL_OP_ENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaEnable);
	else
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaEnable);

	if (op & QIB_SDMA_SENDCTRL_OP_INTENABLE)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaIntEnable);
	else
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaIntEnable);

	if (op & QIB_SDMA_SENDCTRL_OP_HALT)
		set_sendctrl |= SYM_MASK(SendCtrl, SDmaHalt);
	else
		clr_sendctrl |= SYM_MASK(SendCtrl, SDmaHalt);

	spin_lock(&dd->sendctrl_lock);

	dd->sendctrl |= set_sendctrl;
	dd->sendctrl &= ~clr_sendctrl;

	qib_write_kreg(dd, kr_sendctrl, dd->sendctrl);
	qib_write_kreg(dd, kr_scratch, 0);

	spin_unlock(&dd->sendctrl_lock);
}