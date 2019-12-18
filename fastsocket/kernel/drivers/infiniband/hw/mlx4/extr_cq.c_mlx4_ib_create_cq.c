#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct mlx4_uar {int dummy; } ;
struct mlx4_ib_dev {int* eq_table; TYPE_3__* dev; struct mlx4_uar priv_uar; } ;
struct mlx4_ib_create_cq {int /*<<< orphan*/  db_addr; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_22__ {int /*<<< orphan*/  dma; scalar_t__* db; } ;
struct ib_cq {int cqe; } ;
struct TYPE_21__ {int /*<<< orphan*/  mtt; } ;
struct TYPE_17__ {int /*<<< orphan*/  cqn; int /*<<< orphan*/  event; int /*<<< orphan*/  comp; scalar_t__* arm_db; scalar_t__* set_ci_db; } ;
struct mlx4_ib_cq {TYPE_7__ db; struct ib_cq ibcq; TYPE_4__ buf; int /*<<< orphan*/  umem; TYPE_16__ mcq; int /*<<< orphan*/ * resize_umem; int /*<<< orphan*/ * resize_buf; int /*<<< orphan*/  lock; int /*<<< orphan*/  resize_mutex; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int num_comp_vectors; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_18__ {int max_cqes; } ;
struct TYPE_20__ {TYPE_1__ caps; } ;
struct TYPE_19__ {struct mlx4_uar uar; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ib_copy_from_udata (struct mlx4_ib_create_cq*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_cq*) ; 
 struct mlx4_ib_cq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_cq_alloc (TYPE_3__*,int,int /*<<< orphan*/ *,struct mlx4_uar*,int /*<<< orphan*/ ,TYPE_16__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_db_alloc (TYPE_3__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  mlx4_db_free (TYPE_3__*,TYPE_7__*) ; 
 int mlx4_ib_alloc_cq_buf (struct mlx4_ib_dev*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  mlx4_ib_cq_comp ; 
 int /*<<< orphan*/  mlx4_ib_cq_event ; 
 int mlx4_ib_db_map_user (TYPE_2__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  mlx4_ib_db_unmap_user (TYPE_2__*,TYPE_7__*) ; 
 int /*<<< orphan*/  mlx4_ib_free_cq_buf (struct mlx4_ib_dev*,TYPE_4__*,int) ; 
 int mlx4_ib_get_cq_umem (struct mlx4_ib_dev*,struct ib_ucontext*,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 
 TYPE_2__* to_mucontext (struct ib_ucontext*) ; 

struct ib_cq *mlx4_ib_create_cq(struct ib_device *ibdev, int entries, int vector,
				struct ib_ucontext *context,
				struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	struct mlx4_ib_cq *cq;
	struct mlx4_uar *uar;
	int err;

	if (entries < 1 || entries > dev->dev->caps.max_cqes)
		return ERR_PTR(-EINVAL);

	cq = kmalloc(sizeof *cq, GFP_KERNEL);
	if (!cq)
		return ERR_PTR(-ENOMEM);

	entries      = roundup_pow_of_two(entries + 1);
	cq->ibcq.cqe = entries - 1;
	mutex_init(&cq->resize_mutex);
	spin_lock_init(&cq->lock);
	cq->resize_buf = NULL;
	cq->resize_umem = NULL;

	if (context) {
		struct mlx4_ib_create_cq ucmd;

		if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd)) {
			err = -EFAULT;
			goto err_cq;
		}

		err = mlx4_ib_get_cq_umem(dev, context, &cq->buf, &cq->umem,
					  ucmd.buf_addr, entries);
		if (err)
			goto err_cq;

		err = mlx4_ib_db_map_user(to_mucontext(context), ucmd.db_addr,
					  &cq->db);
		if (err)
			goto err_mtt;

		uar = &to_mucontext(context)->uar;
	} else {
		err = mlx4_db_alloc(dev->dev, &cq->db, 1);
		if (err)
			goto err_cq;

		cq->mcq.set_ci_db  = cq->db.db;
		cq->mcq.arm_db     = cq->db.db + 1;
		*cq->mcq.set_ci_db = 0;
		*cq->mcq.arm_db    = 0;

		err = mlx4_ib_alloc_cq_buf(dev, &cq->buf, entries);
		if (err)
			goto err_db;

		uar = &dev->priv_uar;
	}

	if (dev->eq_table)
		vector = dev->eq_table[vector % ibdev->num_comp_vectors];

	err = mlx4_cq_alloc(dev->dev, entries, &cq->buf.mtt, uar,
			    cq->db.dma, &cq->mcq, vector, 0, 0);
	if (err)
		goto err_dbmap;

	cq->mcq.comp  = mlx4_ib_cq_comp;
	cq->mcq.event = mlx4_ib_cq_event;

	if (context)
		if (ib_copy_to_udata(udata, &cq->mcq.cqn, sizeof (__u32))) {
			err = -EFAULT;
			goto err_dbmap;
		}

	return &cq->ibcq;

err_dbmap:
	if (context)
		mlx4_ib_db_unmap_user(to_mucontext(context), &cq->db);

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &cq->buf.mtt);

	if (context)
		ib_umem_release(cq->umem);
	else
		mlx4_ib_free_cq_buf(dev, &cq->buf, cq->ibcq.cqe);

err_db:
	if (!context)
		mlx4_db_free(dev->dev, &cq->db);

err_cq:
	kfree(cq);

	return ERR_PTR(err);
}