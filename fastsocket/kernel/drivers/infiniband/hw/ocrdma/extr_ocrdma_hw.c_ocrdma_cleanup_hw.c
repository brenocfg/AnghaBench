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
struct ocrdma_dev {int /*<<< orphan*/  meq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocrdma_destroy_eq (struct ocrdma_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_destroy_mq (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_destroy_qp_eqs (struct ocrdma_dev*) ; 
 int /*<<< orphan*/  ocrdma_mbx_delete_ah_tbl (struct ocrdma_dev*) ; 

void ocrdma_cleanup_hw(struct ocrdma_dev *dev)
{
	ocrdma_mbx_delete_ah_tbl(dev);

	/* cleanup the data path eqs */
	ocrdma_destroy_qp_eqs(dev);

	/* cleanup the control path */
	ocrdma_destroy_mq(dev);
	ocrdma_destroy_eq(dev, &dev->meq);
}