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
struct qib_fmr {TYPE_1__ mr; } ;
struct ib_fmr {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  deinit_qib_mregion (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct qib_fmr*) ; 
 int /*<<< orphan*/  qib_free_lkey (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_get_mr (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_put_mr (TYPE_1__*) ; 
 struct qib_fmr* to_ifmr (struct ib_fmr*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int qib_dealloc_fmr(struct ib_fmr *ibfmr)
{
	struct qib_fmr *fmr = to_ifmr(ibfmr);
	int ret = 0;
	unsigned long timeout;

	qib_free_lkey(&fmr->mr);
	qib_put_mr(&fmr->mr); /* will set completion if last */
	timeout = wait_for_completion_timeout(&fmr->mr.comp,
		5 * HZ);
	if (!timeout) {
		qib_get_mr(&fmr->mr);
		ret = -EBUSY;
		goto out;
	}
	deinit_qib_mregion(&fmr->mr);
	kfree(fmr);
out:
	return ret;
}