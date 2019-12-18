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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct nes_device {TYPE_2__ cqp; int /*<<< orphan*/  cqp_avail_reqs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * wqe_words; } ;
struct nes_cqp_request {int /*<<< orphan*/  list; scalar_t__ dynamic; TYPE_1__ cqp_wqe; } ;

/* Variables and functions */
 size_t NES_CQP_WQE_OPCODE_IDX ; 
 int /*<<< orphan*/  NES_DBG_CQP ; 
 int /*<<< orphan*/  kfree (struct nes_cqp_request*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cqp_request*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void nes_free_cqp_request(struct nes_device *nesdev,
			  struct nes_cqp_request *cqp_request)
{
	unsigned long flags;

	nes_debug(NES_DBG_CQP, "CQP request %p (opcode 0x%02X) freed.\n",
		  cqp_request,
		  le32_to_cpu(cqp_request->cqp_wqe.wqe_words[NES_CQP_WQE_OPCODE_IDX]) & 0x3f);

	if (cqp_request->dynamic) {
		kfree(cqp_request);
	} else {
		spin_lock_irqsave(&nesdev->cqp.lock, flags);
		list_add_tail(&cqp_request->list, &nesdev->cqp_avail_reqs);
		spin_unlock_irqrestore(&nesdev->cqp.lock, flags);
	}
}