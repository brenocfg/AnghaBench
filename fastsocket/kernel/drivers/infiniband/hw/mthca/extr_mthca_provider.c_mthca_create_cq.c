#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct mthca_create_cq {int /*<<< orphan*/  set_db_index; int /*<<< orphan*/  arm_db_index; int /*<<< orphan*/  pdn; int /*<<< orphan*/  lkey; int /*<<< orphan*/  arm_db_page; int /*<<< orphan*/  set_db_page; } ;
struct ib_cq {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_15__ {TYPE_2__ ibmr; } ;
struct TYPE_16__ {TYPE_3__ mr; } ;
struct mthca_cq {struct ib_cq ibcq; int /*<<< orphan*/ * resize_buf; int /*<<< orphan*/  cqn; int /*<<< orphan*/  arm_db_index; int /*<<< orphan*/  set_ci_db_index; TYPE_4__ buf; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_17__ {int /*<<< orphan*/  pd_num; } ;
struct TYPE_13__ {int max_cqes; } ;
struct TYPE_19__ {TYPE_5__ driver_pd; TYPE_1__ limits; } ;
struct TYPE_18__ {int /*<<< orphan*/  db_tab; int /*<<< orphan*/  uar; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_copy_from_udata (struct mthca_create_cq*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mthca_cq*) ; 
 struct mthca_cq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_cq (TYPE_7__*,struct mthca_cq*) ; 
 int mthca_init_cq (TYPE_7__*,int,TYPE_6__*,int /*<<< orphan*/ ,struct mthca_cq*) ; 
 int mthca_map_user_db (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_unmap_user_db (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* to_mdev (struct ib_device*) ; 
 TYPE_6__* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static struct ib_cq *mthca_create_cq(struct ib_device *ibdev, int entries,
				     int comp_vector,
				     struct ib_ucontext *context,
				     struct ib_udata *udata)
{
	struct mthca_create_cq ucmd;
	struct mthca_cq *cq;
	int nent;
	int err;

	if (entries < 1 || entries > to_mdev(ibdev)->limits.max_cqes)
		return ERR_PTR(-EINVAL);

	if (context) {
		if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd))
			return ERR_PTR(-EFAULT);

		err = mthca_map_user_db(to_mdev(ibdev), &to_mucontext(context)->uar,
					to_mucontext(context)->db_tab,
					ucmd.set_db_index, ucmd.set_db_page);
		if (err)
			return ERR_PTR(err);

		err = mthca_map_user_db(to_mdev(ibdev), &to_mucontext(context)->uar,
					to_mucontext(context)->db_tab,
					ucmd.arm_db_index, ucmd.arm_db_page);
		if (err)
			goto err_unmap_set;
	}

	cq = kmalloc(sizeof *cq, GFP_KERNEL);
	if (!cq) {
		err = -ENOMEM;
		goto err_unmap_arm;
	}

	if (context) {
		cq->buf.mr.ibmr.lkey = ucmd.lkey;
		cq->set_ci_db_index  = ucmd.set_db_index;
		cq->arm_db_index     = ucmd.arm_db_index;
	}

	for (nent = 1; nent <= entries; nent <<= 1)
		; /* nothing */

	err = mthca_init_cq(to_mdev(ibdev), nent,
			    context ? to_mucontext(context) : NULL,
			    context ? ucmd.pdn : to_mdev(ibdev)->driver_pd.pd_num,
			    cq);
	if (err)
		goto err_free;

	if (context && ib_copy_to_udata(udata, &cq->cqn, sizeof (__u32))) {
		mthca_free_cq(to_mdev(ibdev), cq);
		goto err_free;
	}

	cq->resize_buf = NULL;

	return &cq->ibcq;

err_free:
	kfree(cq);

err_unmap_arm:
	if (context)
		mthca_unmap_user_db(to_mdev(ibdev), &to_mucontext(context)->uar,
				    to_mucontext(context)->db_tab, ucmd.arm_db_index);

err_unmap_set:
	if (context)
		mthca_unmap_user_db(to_mdev(ibdev), &to_mucontext(context)->uar,
				    to_mucontext(context)->db_tab, ucmd.set_db_index);

	return ERR_PTR(err);
}