#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_tskim_s {TYPE_2__* fcpim; int /*<<< orphan*/  qe; TYPE_1__* itnim; } ;
struct TYPE_4__ {int /*<<< orphan*/  tskim_free_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  tsk_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_is_on_q_func (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_tskim_free(struct bfa_tskim_s *tskim)
{
	WARN_ON(!bfa_q_is_on_q_func(&tskim->itnim->tsk_q, &tskim->qe));
	list_del(&tskim->qe);
	list_add_tail(&tskim->qe, &tskim->fcpim->tskim_free_q);
}