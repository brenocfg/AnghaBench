#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int access_flags; } ;
struct ib_mr {int dummy; } ;
struct qib_mr {TYPE_2__ mr; struct ib_mr ibmr; } ;
struct ib_pd {int dummy; } ;
struct TYPE_5__ {scalar_t__ user; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  deinit_qib_mregion (TYPE_2__*) ; 
 int init_qib_mregion (TYPE_2__*,struct ib_pd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qib_mr*) ; 
 struct qib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qib_alloc_lkey (TYPE_2__*,int) ; 
 TYPE_1__* to_ipd (struct ib_pd*) ; 

struct ib_mr *qib_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct qib_mr *mr = NULL;
	struct ib_mr *ret;
	int rval;

	if (to_ipd(pd)->user) {
		ret = ERR_PTR(-EPERM);
		goto bail;
	}

	mr = kzalloc(sizeof *mr, GFP_KERNEL);
	if (!mr) {
		ret = ERR_PTR(-ENOMEM);
		goto bail;
	}

	rval = init_qib_mregion(&mr->mr, pd, 0);
	if (rval) {
		ret = ERR_PTR(rval);
		goto bail;
	}


	rval = qib_alloc_lkey(&mr->mr, 1);
	if (rval) {
		ret = ERR_PTR(rval);
		goto bail_mregion;
	}

	mr->mr.access_flags = acc;
	ret = &mr->ibmr;
done:
	return ret;

bail_mregion:
	deinit_qib_mregion(&mr->mr);
bail:
	kfree(mr);
	goto done;
}