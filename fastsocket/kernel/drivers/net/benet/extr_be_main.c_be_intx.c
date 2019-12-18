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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct be_eq_obj {scalar_t__ spurious_intr; TYPE_1__ q; int /*<<< orphan*/  napi; struct be_adapter* adapter; } ;
struct be_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_eq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int,int) ; 
 int events_get (struct be_eq_obj*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t be_intx(int irq, void *dev)
{
	struct be_eq_obj *eqo = dev;
	struct be_adapter *adapter = eqo->adapter;
	int num_evts = 0;

	/* IRQ is not expected when NAPI is scheduled as the EQ
	 * will not be armed.
	 * But, this can happen on Lancer INTx where it takes
	 * a while to de-assert INTx or in BE2 where occasionaly
	 * an interrupt may be raised even when EQ is unarmed.
	 * If NAPI is already scheduled, then counting & notifying
	 * events will orphan them.
	 */
	if (napi_schedule_prep(&eqo->napi)) {
		num_evts = events_get(eqo);
		__napi_schedule(&eqo->napi);
		if (num_evts)
			eqo->spurious_intr = 0;
	}
	be_eq_notify(adapter, eqo->q.id, false, true, num_evts);

	/* Return IRQ_HANDLED only for the the first spurious intr
	 * after a valid intr to stop the kernel from branding
	 * this irq as a bad one!
	 */
	if (num_evts || eqo->spurious_intr++ == 0)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}