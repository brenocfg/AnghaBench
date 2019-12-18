#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ uobject; } ;
struct TYPE_5__ {int /*<<< orphan*/  scq; int /*<<< orphan*/  rcq; } ;
struct iwch_qp {int /*<<< orphan*/  wq; TYPE_2__ ibqp; TYPE_1__ attr; int /*<<< orphan*/  rhp; } ;
struct TYPE_7__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct iwch_cq {int /*<<< orphan*/  comp_handler_lock; TYPE_3__ ibcq; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_qp (struct iwch_qp*,struct iwch_cq*,struct iwch_cq*) ; 
 int /*<<< orphan*/  cxio_set_cq_in_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxio_set_wq_in_error (int /*<<< orphan*/ *) ; 
 struct iwch_cq* get_chp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_qp(struct iwch_qp *qhp)
{
	struct iwch_cq *rchp, *schp;

	rchp = get_chp(qhp->rhp, qhp->attr.rcq);
	schp = get_chp(qhp->rhp, qhp->attr.scq);

	if (qhp->ibqp.uobject) {
		cxio_set_wq_in_error(&qhp->wq);
		cxio_set_cq_in_error(&rchp->cq);
		spin_lock(&rchp->comp_handler_lock);
		(*rchp->ibcq.comp_handler)(&rchp->ibcq, rchp->ibcq.cq_context);
		spin_unlock(&rchp->comp_handler_lock);
		if (schp != rchp) {
			cxio_set_cq_in_error(&schp->cq);
			spin_lock(&schp->comp_handler_lock);
			(*schp->ibcq.comp_handler)(&schp->ibcq,
						   schp->ibcq.cq_context);
			spin_unlock(&schp->comp_handler_lock);
		}
		return;
	}
	__flush_qp(qhp, rchp, schp);
}