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
struct mthca_qp {scalar_t__ qpn; } ;
struct TYPE_2__ {scalar_t__ sqp_start; } ;
struct mthca_dev {TYPE_1__ qp_table; } ;

/* Variables and functions */

__attribute__((used)) static int is_sqp(struct mthca_dev *dev, struct mthca_qp *qp)
{
	return qp->qpn >= dev->qp_table.sqp_start &&
		qp->qpn <= dev->qp_table.sqp_start + 3;
}