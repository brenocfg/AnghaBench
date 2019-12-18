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
struct ib_pd {int /*<<< orphan*/  usecnt; } ;
struct ehca_shca {struct ehca_mr* maxmr; int /*<<< orphan*/  ib_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  lkey; struct ib_pd* pd; } ;
struct TYPE_3__ {TYPE_2__ ib_mr; } ;
struct ehca_mr {TYPE_1__ ib; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int ehca_dereg_mr (TYPE_2__*) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,...) ; 

int ehca_dereg_internal_maxmr(struct ehca_shca *shca)
{
	int ret;
	struct ehca_mr *e_maxmr;
	struct ib_pd *ib_pd;

	if (!shca->maxmr) {
		ehca_err(&shca->ib_device, "bad call, shca=%p", shca);
		ret = -EINVAL;
		goto ehca_dereg_internal_maxmr_exit0;
	}

	e_maxmr = shca->maxmr;
	ib_pd = e_maxmr->ib.ib_mr.pd;
	shca->maxmr = NULL; /* remove internal max-MR indication from SHCA */

	ret = ehca_dereg_mr(&e_maxmr->ib.ib_mr);
	if (ret) {
		ehca_err(&shca->ib_device, "dereg internal max-MR failed, "
			 "ret=%i e_maxmr=%p shca=%p lkey=%x",
			 ret, e_maxmr, shca, e_maxmr->ib.ib_mr.lkey);
		shca->maxmr = e_maxmr;
		goto ehca_dereg_internal_maxmr_exit0;
	}

	atomic_dec(&ib_pd->usecnt);

ehca_dereg_internal_maxmr_exit0:
	if (ret)
		ehca_err(&shca->ib_device, "ret=%i shca=%p shca->maxmr=%p",
			 ret, shca, shca->maxmr);
	return ret;
}