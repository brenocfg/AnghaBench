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
struct nes_qp {int /*<<< orphan*/  ibqp; } ;
struct disconn_work {int /*<<< orphan*/  work; struct nes_qp* nesqp; } ;
struct TYPE_2__ {int /*<<< orphan*/  disconn_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_cm_core ; 
 struct disconn_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_add_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_disconnect_worker ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nes_cm_disconn(struct nes_qp *nesqp)
{
	struct disconn_work *work;

	work = kzalloc(sizeof *work, GFP_ATOMIC);
	if (!work)
		return -ENOMEM;  /* Timer will clean up */

	nes_add_ref(&nesqp->ibqp);
	work->nesqp = nesqp;
	INIT_WORK(&work->work, nes_disconnect_worker);
	queue_work(g_cm_core->disconn_wq, &work->work);
	return 0;
}