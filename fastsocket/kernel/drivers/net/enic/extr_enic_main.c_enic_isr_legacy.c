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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct enic {int /*<<< orphan*/ * intr; int /*<<< orphan*/ * napi; int /*<<< orphan*/  reset; int /*<<< orphan*/  legacy_pba; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ ENIC_TEST_INTR (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 unsigned int enic_legacy_err_intr () ; 
 unsigned int enic_legacy_io_intr () ; 
 unsigned int enic_legacy_notify_intr () ; 
 int /*<<< orphan*/  enic_log_q_error (struct enic*) ; 
 int /*<<< orphan*/  enic_notify_check (struct enic*) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_legacy_pba (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_all_credits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_unmask (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t enic_isr_legacy(int irq, void *data)
{
	struct net_device *netdev = data;
	struct enic *enic = netdev_priv(netdev);
	unsigned int io_intr = enic_legacy_io_intr();
	unsigned int err_intr = enic_legacy_err_intr();
	unsigned int notify_intr = enic_legacy_notify_intr();
	u32 pba;

	vnic_intr_mask(&enic->intr[io_intr]);

	pba = vnic_intr_legacy_pba(enic->legacy_pba);
	if (!pba) {
		vnic_intr_unmask(&enic->intr[io_intr]);
		return IRQ_NONE;	/* not our interrupt */
	}

	if (ENIC_TEST_INTR(pba, notify_intr)) {
		vnic_intr_return_all_credits(&enic->intr[notify_intr]);
		enic_notify_check(enic);
	}

	if (ENIC_TEST_INTR(pba, err_intr)) {
		vnic_intr_return_all_credits(&enic->intr[err_intr]);
		enic_log_q_error(enic);
		/* schedule recovery from WQ/RQ error */
		schedule_work(&enic->reset);
		return IRQ_HANDLED;
	}

	if (ENIC_TEST_INTR(pba, io_intr)) {
		if (napi_schedule_prep(&enic->napi[0]))
			__napi_schedule(&enic->napi[0]);
	} else {
		vnic_intr_unmask(&enic->intr[io_intr]);
	}

	return IRQ_HANDLED;
}