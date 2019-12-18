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
typedef  int /*<<< orphan*/  u32 ;
struct ocrdma_pd {TYPE_2__* uctx; int /*<<< orphan*/  id; struct ocrdma_dev* dev; } ;
struct ocrdma_dev {int dummy; } ;
struct ib_ah {int dummy; } ;
struct ocrdma_ah {struct ib_ah ibah; int /*<<< orphan*/  id; struct ocrdma_dev* dev; } ;
struct ib_pd {int dummy; } ;
struct ib_ah_attr {int ah_flags; int dlid; } ;
struct TYPE_3__ {int /*<<< orphan*/ * va; } ;
struct TYPE_4__ {TYPE_1__ ah_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_ah* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IB_AH_GRH ; 
 struct ocrdma_pd* get_ocrdma_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct ocrdma_ah*) ; 
 struct ocrdma_ah* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ocrdma_alloc_av (struct ocrdma_dev*,struct ocrdma_ah*) ; 
 int /*<<< orphan*/  ocrdma_free_av (struct ocrdma_dev*,struct ocrdma_ah*) ; 
 int set_av_attr (struct ocrdma_ah*,struct ib_ah_attr*,int /*<<< orphan*/ ) ; 

struct ib_ah *ocrdma_create_ah(struct ib_pd *ibpd, struct ib_ah_attr *attr)
{
	u32 *ahid_addr;
	int status;
	struct ocrdma_ah *ah;
	struct ocrdma_pd *pd = get_ocrdma_pd(ibpd);
	struct ocrdma_dev *dev = pd->dev;

	if (!(attr->ah_flags & IB_AH_GRH))
		return ERR_PTR(-EINVAL);

	ah = kzalloc(sizeof *ah, GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);
	ah->dev = pd->dev;

	status = ocrdma_alloc_av(dev, ah);
	if (status)
		goto av_err;
	status = set_av_attr(ah, attr, pd->id);
	if (status)
		goto av_conf_err;

	/* if pd is for the user process, pass the ah_id to user space */
	if ((pd->uctx) && (pd->uctx->ah_tbl.va)) {
		ahid_addr = pd->uctx->ah_tbl.va + attr->dlid;
		*ahid_addr = ah->id;
	}
	return &ah->ibah;

av_conf_err:
	ocrdma_free_av(dev, ah);
av_err:
	kfree(ah);
	return ERR_PTR(status);
}