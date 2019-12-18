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
struct ib_udata {int dummy; } ;
struct ib_qp_init_attr {int dummy; } ;
struct ib_qp {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ehca_qp {struct ib_qp ib_qp; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ehca_qp*) ; 
 struct ehca_qp* internal_create_qp (struct ib_pd*,struct ib_qp_init_attr*,int /*<<< orphan*/ *,struct ib_udata*,int /*<<< orphan*/ ) ; 

struct ib_qp *ehca_create_qp(struct ib_pd *pd,
			     struct ib_qp_init_attr *qp_init_attr,
			     struct ib_udata *udata)
{
	struct ehca_qp *ret;

	ret = internal_create_qp(pd, qp_init_attr, NULL, udata, 0);
	return IS_ERR(ret) ? (struct ib_qp *)ret : &ret->ib_qp;
}