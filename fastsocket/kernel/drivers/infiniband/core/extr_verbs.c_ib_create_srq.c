#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* cq; TYPE_4__* xrcd; } ;
struct TYPE_10__ {TYPE_2__ xrc; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; TYPE_3__ ext; int /*<<< orphan*/  srq_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_13__ {TYPE_5__* cq; TYPE_4__* xrcd; } ;
struct TYPE_14__ {TYPE_6__ xrc; } ;
struct ib_srq {scalar_t__ srq_type; int /*<<< orphan*/  usecnt; TYPE_7__ ext; int /*<<< orphan*/  srq_context; int /*<<< orphan*/  event_handler; int /*<<< orphan*/ * uobject; struct ib_pd* pd; TYPE_1__* device; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct TYPE_12__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_8__ {struct ib_srq* (* create_srq ) (struct ib_pd*,struct ib_srq_init_attr*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct ib_srq* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IB_SRQT_XRC ; 
 int /*<<< orphan*/  IS_ERR (struct ib_srq*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ib_srq* stub1 (struct ib_pd*,struct ib_srq_init_attr*,int /*<<< orphan*/ *) ; 

struct ib_srq *ib_create_srq(struct ib_pd *pd,
			     struct ib_srq_init_attr *srq_init_attr)
{
	struct ib_srq *srq;

	if (!pd->device->create_srq)
		return ERR_PTR(-ENOSYS);

	srq = pd->device->create_srq(pd, srq_init_attr, NULL);

	if (!IS_ERR(srq)) {
		srq->device    	   = pd->device;
		srq->pd        	   = pd;
		srq->uobject       = NULL;
		srq->event_handler = srq_init_attr->event_handler;
		srq->srq_context   = srq_init_attr->srq_context;
		srq->srq_type      = srq_init_attr->srq_type;
		if (srq->srq_type == IB_SRQT_XRC) {
			srq->ext.xrc.xrcd = srq_init_attr->ext.xrc.xrcd;
			srq->ext.xrc.cq   = srq_init_attr->ext.xrc.cq;
			atomic_inc(&srq->ext.xrc.xrcd->usecnt);
			atomic_inc(&srq->ext.xrc.cq->usecnt);
		}
		atomic_inc(&pd->usecnt);
		atomic_set(&srq->usecnt, 0);
	}

	return srq;
}