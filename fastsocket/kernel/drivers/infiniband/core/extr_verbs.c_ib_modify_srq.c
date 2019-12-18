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
struct ib_srq_attr {int dummy; } ;
struct ib_srq {TYPE_1__* device; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;
struct TYPE_2__ {int (* modify_srq ) (struct ib_srq*,struct ib_srq_attr*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 int stub1 (struct ib_srq*,struct ib_srq_attr*,int,int /*<<< orphan*/ *) ; 

int ib_modify_srq(struct ib_srq *srq,
		  struct ib_srq_attr *srq_attr,
		  enum ib_srq_attr_mask srq_attr_mask)
{
	return srq->device->modify_srq ?
		srq->device->modify_srq(srq, srq_attr, srq_attr_mask, NULL) :
		-ENOSYS;
}