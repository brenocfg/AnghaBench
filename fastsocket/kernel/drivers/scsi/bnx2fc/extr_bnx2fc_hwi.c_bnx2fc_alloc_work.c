#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct bnx2fc_work {int /*<<< orphan*/  wqe; struct bnx2fc_rport* tgt; int /*<<< orphan*/  list; } ;
struct bnx2fc_rport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct bnx2fc_work* kzalloc (int,int /*<<< orphan*/ ) ; 

struct bnx2fc_work *bnx2fc_alloc_work(struct bnx2fc_rport *tgt, u16 wqe)
{
	struct bnx2fc_work *work;
	work = kzalloc(sizeof(struct bnx2fc_work), GFP_ATOMIC);
	if (!work)
		return NULL;

	INIT_LIST_HEAD(&work->list);
	work->tgt = tgt;
	work->wqe = wqe;
	return work;
}