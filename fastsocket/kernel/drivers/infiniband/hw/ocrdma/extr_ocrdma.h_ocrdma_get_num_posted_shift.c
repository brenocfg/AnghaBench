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
struct ocrdma_qp {int id; TYPE_2__* dev; } ;
struct TYPE_3__ {scalar_t__ dev_family; } ;
struct TYPE_4__ {TYPE_1__ nic_info; } ;

/* Variables and functions */
 scalar_t__ OCRDMA_GEN2_FAMILY ; 

__attribute__((used)) static inline int ocrdma_get_num_posted_shift(struct ocrdma_qp *qp)
{
	return ((qp->dev->nic_info.dev_family == OCRDMA_GEN2_FAMILY &&
		 qp->id < 64) ? 24 : 16);
}