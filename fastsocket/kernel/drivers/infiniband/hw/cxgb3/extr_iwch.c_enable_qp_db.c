#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  qpid; } ;
struct iwch_qp {TYPE_4__ wq; TYPE_3__* rhp; } ;
struct TYPE_5__ {int /*<<< orphan*/  doorbell; } ;
struct TYPE_6__ {TYPE_1__ ctrl_qp; } ;
struct TYPE_7__ {TYPE_2__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxio_enable_wq_db (TYPE_4__*) ; 
 int /*<<< orphan*/  ring_doorbell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enable_qp_db(int id, void *p, void *data)
{
	struct iwch_qp *qhp = p;

	if (data)
		ring_doorbell(qhp->rhp->rdev.ctrl_qp.doorbell, qhp->wq.qpid);
	cxio_enable_wq_db(&qhp->wq);
	return 0;
}