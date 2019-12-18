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
struct ib_pd {int dummy; } ;
struct ocrdma_pd {int dpp_enabled; struct ib_pd ibpd; int /*<<< orphan*/  num_dpp_qp; struct ocrdma_dev* dev; } ;
struct TYPE_2__ {scalar_t__ dev_family; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OCRDMA_GEN2_FAMILY ; 
 int /*<<< orphan*/  OCRDMA_PD_MAX_DPP_ENABLED_QP ; 
 struct ocrdma_dev* get_ocrdma_dev (struct ib_device*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_pd*) ; 
 struct ocrdma_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ocrdma_copy_pd_uresp (struct ocrdma_pd*,struct ib_ucontext*,struct ib_udata*) ; 
 int /*<<< orphan*/  ocrdma_dealloc_pd (struct ib_pd*) ; 
 int ocrdma_mbx_alloc_pd (struct ocrdma_dev*,struct ocrdma_pd*) ; 

struct ib_pd *ocrdma_alloc_pd(struct ib_device *ibdev,
			      struct ib_ucontext *context,
			      struct ib_udata *udata)
{
	struct ocrdma_dev *dev = get_ocrdma_dev(ibdev);
	struct ocrdma_pd *pd;
	int status;

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return ERR_PTR(-ENOMEM);
	pd->dev = dev;
	if (udata && context) {
		pd->dpp_enabled = (dev->nic_info.dev_family ==
					OCRDMA_GEN2_FAMILY) ? true : false;
		pd->num_dpp_qp =
			pd->dpp_enabled ? OCRDMA_PD_MAX_DPP_ENABLED_QP : 0;
	}
	status = ocrdma_mbx_alloc_pd(dev, pd);
	if (status) {
		kfree(pd);
		return ERR_PTR(status);
	}

	if (udata && context) {
		status = ocrdma_copy_pd_uresp(pd, context, udata);
		if (status)
			goto err;
	}
	return &pd->ibpd;

err:
	ocrdma_dealloc_pd(&pd->ibpd);
	return ERR_PTR(status);
}