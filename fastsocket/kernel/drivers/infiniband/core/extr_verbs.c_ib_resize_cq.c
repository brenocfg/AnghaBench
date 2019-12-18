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
struct ib_cq {TYPE_1__* device; } ;
struct TYPE_2__ {int (* resize_cq ) (struct ib_cq*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_cq*,int,int /*<<< orphan*/ *) ; 

int ib_resize_cq(struct ib_cq *cq, int cqe)
{
	return cq->device->resize_cq ?
		cq->device->resize_cq(cq, cqe, NULL) : -ENOSYS;
}