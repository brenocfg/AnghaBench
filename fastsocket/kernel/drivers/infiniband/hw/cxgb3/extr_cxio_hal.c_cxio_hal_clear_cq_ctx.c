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
typedef  int /*<<< orphan*/  u32 ;
struct rdma_cq_setup {scalar_t__ ovfl_mode; scalar_t__ credit_thres; scalar_t__ credits; scalar_t__ size; scalar_t__ base_addr; int /*<<< orphan*/  id; } ;
struct cxio_rdev {TYPE_1__* t3cdev_p; } ;
struct TYPE_2__ {int (* ctl ) (TYPE_1__*,int /*<<< orphan*/ ,struct rdma_cq_setup*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CQ_SETUP ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,struct rdma_cq_setup*) ; 

__attribute__((used)) static int cxio_hal_clear_cq_ctx(struct cxio_rdev *rdev_p, u32 cqid)
{
	struct rdma_cq_setup setup;
	setup.id = cqid;
	setup.base_addr = 0;	/* NULL address */
	setup.size = 0;		/* disaable the CQ */
	setup.credits = 0;
	setup.credit_thres = 0;
	setup.ovfl_mode = 0;
	return (rdev_p->t3cdev_p->ctl(rdev_p->t3cdev_p, RDMA_CQ_SETUP, &setup));
}