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
struct vnic_intr {TYPE_1__* ctrl; int /*<<< orphan*/  vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  coalescing_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_intr_coal_timer_usec_to_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnic_intr_coalescing_timer_set(struct vnic_intr *intr,
	u32 coalescing_timer)
{
	iowrite32(vnic_dev_intr_coal_timer_usec_to_hw(intr->vdev,
		coalescing_timer), &intr->ctrl->coalescing_timer);
}