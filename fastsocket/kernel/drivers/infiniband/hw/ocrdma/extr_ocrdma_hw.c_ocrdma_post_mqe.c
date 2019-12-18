#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tag_lo; } ;
struct ocrdma_mqe {TYPE_3__ hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  head; } ;
struct TYPE_5__ {TYPE_4__ sq; } ;
struct TYPE_6__ {int cmd_done; int /*<<< orphan*/  tag; } ;
struct ocrdma_dev {TYPE_1__ mq; TYPE_2__ mqe_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocrdma_copy_cpu_to_le32 (struct ocrdma_mqe*,struct ocrdma_mqe*,int) ; 
 struct ocrdma_mqe* ocrdma_get_mqe (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_mq_inc_head (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_ring_mq_db (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ocrdma_post_mqe(struct ocrdma_dev *dev, struct ocrdma_mqe *cmd)
{
	struct ocrdma_mqe *mqe;

	dev->mqe_ctx.tag = dev->mq.sq.head;
	dev->mqe_ctx.cmd_done = false;
	mqe = ocrdma_get_mqe(dev);
	cmd->hdr.tag_lo = dev->mq.sq.head;
	ocrdma_copy_cpu_to_le32(mqe, cmd, sizeof(*mqe));
	/* make sure descriptor is written before ringing doorbell */
	wmb();
	ocrdma_mq_inc_head(dev);
	ocrdma_ring_mq_db(dev);
}