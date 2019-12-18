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
struct kwqe {int kwqe_op_flag; } ;
struct cnic_dev {int /*<<< orphan*/  (* submit_kwqes ) (struct cnic_dev*,struct kwqe**,int) ;} ;
typedef  int /*<<< orphan*/  l2kwqe ;

/* Variables and functions */
 int KWQE_LAYER_SHIFT ; 
 int KWQE_OPCODE_SHIFT ; 
 int L2_KWQE_OPCODE_VALUE_FLUSH ; 
 int L2_LAYER_CODE ; 
 int /*<<< orphan*/  memset (struct kwqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*,struct kwqe**,int) ; 

__attribute__((used)) static void cnic_shutdown_bnx2_rx_ring(struct cnic_dev *dev)
{
	struct kwqe *wqes[1], l2kwqe;

	memset(&l2kwqe, 0, sizeof(l2kwqe));
	wqes[0] = &l2kwqe;
	l2kwqe.kwqe_op_flag = (L2_LAYER_CODE << KWQE_LAYER_SHIFT) |
			      (L2_KWQE_OPCODE_VALUE_FLUSH <<
			       KWQE_OPCODE_SHIFT) | 2;
	dev->submit_kwqes(dev, wqes, 1);
}