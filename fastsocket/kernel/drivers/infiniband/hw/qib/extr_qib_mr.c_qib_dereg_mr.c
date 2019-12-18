#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  comp; } ;
struct qib_mr {scalar_t__ umem; TYPE_1__ mr; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  deinit_qib_mregion (TYPE_1__*) ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct qib_mr*) ; 
 int /*<<< orphan*/  qib_free_lkey (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_get_mr (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_put_mr (TYPE_1__*) ; 
 struct qib_mr* to_imr (struct ib_mr*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int qib_dereg_mr(struct ib_mr *ibmr)
{
	struct qib_mr *mr = to_imr(ibmr);
	int ret = 0;
	unsigned long timeout;

	qib_free_lkey(&mr->mr);

	qib_put_mr(&mr->mr); /* will set completion if last */
	timeout = wait_for_completion_timeout(&mr->mr.comp,
		5 * HZ);
	if (!timeout) {
		qib_get_mr(&mr->mr);
		ret = -EBUSY;
		goto out;
	}
	deinit_qib_mregion(&mr->mr);
	if (mr->umem)
		ib_umem_release(mr->umem);
	kfree(mr);
out:
	return ret;
}