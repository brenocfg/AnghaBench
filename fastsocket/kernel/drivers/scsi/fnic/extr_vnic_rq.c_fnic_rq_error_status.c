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
struct vnic_rq {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_status; } ;

/* Variables and functions */
 unsigned int ioread32 (int /*<<< orphan*/ *) ; 

unsigned int vnic_rq_error_status(struct vnic_rq *rq)
{
	return ioread32(&rq->ctrl->error_status);
}