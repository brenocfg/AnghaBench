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
struct TYPE_2__ {size_t qp_id; int /*<<< orphan*/  sq_pbase; int /*<<< orphan*/ * sq_vbase; int /*<<< orphan*/  q2_pbase; int /*<<< orphan*/ * q2_vbase; } ;
struct nes_qp {int qp_mem_size; int /*<<< orphan*/  allocated_buffer; TYPE_1__ hwqp; int /*<<< orphan*/ * pbl_vbase; int /*<<< orphan*/  pbl_pbase; } ;
struct nes_device {int /*<<< orphan*/  pcidev; struct nes_adapter* nesadapter; } ;
struct nes_cqp_request {struct nes_qp* cqp_callback_pointer; } ;
struct nes_adapter {int /*<<< orphan*/ ** qp_table; int /*<<< orphan*/  allocated_qps; int /*<<< orphan*/  pbl_lock; int /*<<< orphan*/  free_256pbl; } ;

/* Variables and functions */
 size_t NES_FIRST_QPN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_free_resource (struct nes_adapter*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qps_destroyed ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nes_cqp_rem_ref_callback(struct nes_device *nesdev, struct nes_cqp_request *cqp_request)
{
	unsigned long flags;
	struct nes_qp *nesqp = cqp_request->cqp_callback_pointer;
	struct nes_adapter *nesadapter = nesdev->nesadapter;

	atomic_inc(&qps_destroyed);

	/* Free the control structures */

	if (nesqp->pbl_vbase) {
		pci_free_consistent(nesdev->pcidev, nesqp->qp_mem_size,
				nesqp->hwqp.q2_vbase, nesqp->hwqp.q2_pbase);
		spin_lock_irqsave(&nesadapter->pbl_lock, flags);
		nesadapter->free_256pbl++;
		spin_unlock_irqrestore(&nesadapter->pbl_lock, flags);
		pci_free_consistent(nesdev->pcidev, 256, nesqp->pbl_vbase, nesqp->pbl_pbase);
		nesqp->pbl_vbase = NULL;

	} else {
		pci_free_consistent(nesdev->pcidev, nesqp->qp_mem_size,
				nesqp->hwqp.sq_vbase, nesqp->hwqp.sq_pbase);
	}
	nes_free_resource(nesadapter, nesadapter->allocated_qps, nesqp->hwqp.qp_id);

	nesadapter->qp_table[nesqp->hwqp.qp_id-NES_FIRST_QPN] = NULL;
	kfree(nesqp->allocated_buffer);

}