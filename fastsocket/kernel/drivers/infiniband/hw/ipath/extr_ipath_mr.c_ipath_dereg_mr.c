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
struct TYPE_3__ {int mapsz; struct ipath_mr** map; } ;
struct ipath_mr {scalar_t__ umem; TYPE_1__ mr; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  lk_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  ipath_free_lkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipath_mr*) ; 
 TYPE_2__* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_mr* to_imr (struct ib_mr*) ; 

int ipath_dereg_mr(struct ib_mr *ibmr)
{
	struct ipath_mr *mr = to_imr(ibmr);
	int i;

	ipath_free_lkey(&to_idev(ibmr->device)->lk_table, ibmr->lkey);
	i = mr->mr.mapsz;
	while (i) {
		i--;
		kfree(mr->mr.map[i]);
	}

	if (mr->umem)
		ib_umem_release(mr->umem);

	kfree(mr);
	return 0;
}