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
struct mthca_qp {int qpn; } ;
struct TYPE_2__ {int rdb_shift; int /*<<< orphan*/  qp_table; int /*<<< orphan*/  eqp_table; int /*<<< orphan*/  rdb_table; } ;
struct mthca_dev {TYPE_1__ qp_table; } ;

/* Variables and functions */
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int mthca_table_get (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_table_put (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mthca_map_memfree(struct mthca_dev *dev,
			     struct mthca_qp *qp)
{
	int ret;

	if (mthca_is_memfree(dev)) {
		ret = mthca_table_get(dev, dev->qp_table.qp_table, qp->qpn);
		if (ret)
			return ret;

		ret = mthca_table_get(dev, dev->qp_table.eqp_table, qp->qpn);
		if (ret)
			goto err_qpc;

		ret = mthca_table_get(dev, dev->qp_table.rdb_table,
				      qp->qpn << dev->qp_table.rdb_shift);
		if (ret)
			goto err_eqpc;

	}

	return 0;

err_eqpc:
	mthca_table_put(dev, dev->qp_table.eqp_table, qp->qpn);

err_qpc:
	mthca_table_put(dev, dev->qp_table.qp_table, qp->qpn);

	return ret;
}