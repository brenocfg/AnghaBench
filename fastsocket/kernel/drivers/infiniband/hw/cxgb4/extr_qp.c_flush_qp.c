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
struct c4iw_qp {int /*<<< orphan*/  wq; TYPE_2__ ibqp; TYPE_1__ attr; int /*<<< orphan*/  rhp; } ;
struct TYPE_7__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct c4iw_cq {int /*<<< orphan*/  comp_handler_lock; TYPE_3__ ibcq; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flush_qp (struct c4iw_qp*,struct c4iw_cq*,struct c4iw_cq*) ; 
 struct c4iw_cq* get_chp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_set_cq_in_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_set_wq_in_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_qp(struct c4iw_qp *qhp)
{
	struct c4iw_cq *rchp, *schp;
	unsigned long flag;

	rchp = get_chp(qhp->rhp, qhp->attr.rcq);
	schp = get_chp(qhp->rhp, qhp->attr.scq);

	if (qhp->ibqp.uobject) {
		t4_set_wq_in_error(&qhp->wq);
		t4_set_cq_in_error(&rchp->cq);
		spin_lock_irqsave(&rchp->comp_handler_lock, flag);
		(*rchp->ibcq.comp_handler)(&rchp->ibcq, rchp->ibcq.cq_context);
		spin_unlock_irqrestore(&rchp->comp_handler_lock, flag);
		if (schp != rchp) {
			t4_set_cq_in_error(&schp->cq);
			spin_lock_irqsave(&schp->comp_handler_lock, flag);
			(*schp->ibcq.comp_handler)(&schp->ibcq,
					schp->ibcq.cq_context);
			spin_unlock_irqrestore(&schp->comp_handler_lock, flag);
		}
		return;
	}
	__flush_qp(qhp, rchp, schp);
}