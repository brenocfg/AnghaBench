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
struct ehca_sport {int /*<<< orphan*/  ibcq_aqp1; int /*<<< orphan*/ * ibqp_sqp; } ;

/* Variables and functions */
 size_t IB_QPT_GSI ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int) ; 
 int ib_destroy_cq (int /*<<< orphan*/ ) ; 
 int ib_destroy_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehca_destroy_aqp1(struct ehca_sport *sport)
{
	int ret;

	ret = ib_destroy_qp(sport->ibqp_sqp[IB_QPT_GSI]);
	if (ret) {
		ehca_gen_err("Cannot destroy AQP1 QP. ret=%i", ret);
		return ret;
	}

	ret = ib_destroy_cq(sport->ibcq_aqp1);
	if (ret)
		ehca_gen_err("Cannot destroy AQP1 CQ. ret=%i", ret);

	return ret;
}