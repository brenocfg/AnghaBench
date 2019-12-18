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
typedef  int u32 ;
struct vnic_rq {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  fetch_index; } ;

/* Variables and functions */
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_init_start (struct vnic_rq*,unsigned int,int,int,unsigned int,unsigned int) ; 

void vnic_rq_init(struct vnic_rq *rq, unsigned int cq_index,
	unsigned int error_interrupt_enable,
	unsigned int error_interrupt_offset)
{
	u32 fetch_index;

	/* Use current fetch_index as the ring starting point */
	fetch_index = ioread32(&rq->ctrl->fetch_index);

	if (fetch_index == 0xFFFFFFFF) { /* check for hardware gone  */
		/* Hardware surprise removal: reset fetch_index */
		fetch_index = 0;
	}

	vnic_rq_init_start(rq, cq_index,
		fetch_index, fetch_index,
		error_interrupt_enable,
		error_interrupt_offset);
}