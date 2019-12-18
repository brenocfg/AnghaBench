#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_17__ ;
typedef  struct TYPE_38__   TYPE_16__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_wqe_srq_next_seg {int /*<<< orphan*/  next_wqe_index; } ;
struct mlx4_wqe_data_seg {int /*<<< orphan*/  lkey; } ;
struct TYPE_39__ {int /*<<< orphan*/  dma; scalar_t__* db; } ;
struct TYPE_41__ {int /*<<< orphan*/  page_shift; int /*<<< orphan*/  npages; } ;
struct TYPE_44__ {int /*<<< orphan*/  srq_num; } ;
struct TYPE_45__ {TYPE_4__ xrc; } ;
struct ib_srq {TYPE_5__ ext; } ;
struct TYPE_37__ {int max; scalar_t__ max_gs; int /*<<< orphan*/  srqn; int /*<<< orphan*/  event; int /*<<< orphan*/  wqe_shift; } ;
struct mlx4_ib_srq {int tail; TYPE_17__ db; TYPE_24__ buf; TYPE_16__* umem; int /*<<< orphan*/  mtt; struct mlx4_ib_srq* wrid; struct ib_srq ibsrq; TYPE_13__ msrq; scalar_t__ wqe_ctr; scalar_t__ head; int /*<<< orphan*/  lock; int /*<<< orphan*/  mutex; } ;
struct mlx4_ib_dev {TYPE_12__* dev; } ;
struct mlx4_ib_create_srq {int /*<<< orphan*/  db_addr; int /*<<< orphan*/  buf_addr; } ;
struct ib_udata {int dummy; } ;
struct TYPE_47__ {int max_wr; scalar_t__ max_sge; } ;
struct TYPE_42__ {int /*<<< orphan*/  xrcd; int /*<<< orphan*/  cq; } ;
struct TYPE_43__ {TYPE_2__ xrc; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; TYPE_7__ attr; TYPE_3__ ext; } ;
struct ib_pd {TYPE_8__* uobject; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_49__ {int /*<<< orphan*/  xrcdn; } ;
struct TYPE_48__ {int /*<<< orphan*/  context; } ;
struct TYPE_46__ {int max_srq_wqes; scalar_t__ max_srq_sge; scalar_t__ reserved_xrcds; } ;
struct TYPE_40__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_38__ {int page_size; } ;
struct TYPE_36__ {TYPE_6__ caps; } ;
struct TYPE_35__ {TYPE_1__ mcq; } ;
struct TYPE_34__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_srq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_SRQT_XRC ; 
 scalar_t__ IS_ERR (TYPE_16__*) ; 
 int /*<<< orphan*/  MLX4_INVALID_LKEY ; 
 int PAGE_SIZE ; 
 int PTR_ERR (TYPE_16__*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct mlx4_wqe_srq_next_seg* get_wqe (struct mlx4_ib_srq*,int) ; 
 scalar_t__ ib_copy_from_udata (struct mlx4_ib_create_srq*,struct ib_udata*,int) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 TYPE_16__* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_page_count (TYPE_16__*) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_16__*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_srq*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int max (unsigned long,int) ; 
 scalar_t__ mlx4_buf_alloc (TYPE_12__*,int,int,TYPE_24__*) ; 
 int /*<<< orphan*/  mlx4_buf_free (TYPE_12__*,int,TYPE_24__*) ; 
 int mlx4_buf_write_mtt (TYPE_12__*,int /*<<< orphan*/ *,TYPE_24__*) ; 
 int mlx4_db_alloc (TYPE_12__*,TYPE_17__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_db_free (TYPE_12__*,TYPE_17__*) ; 
 int mlx4_ib_db_map_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__*) ; 
 int /*<<< orphan*/  mlx4_ib_db_unmap_user (int /*<<< orphan*/ ,TYPE_17__*) ; 
 int /*<<< orphan*/  mlx4_ib_srq_event ; 
 int mlx4_ib_umem_write_mtt (struct mlx4_ib_dev*,int /*<<< orphan*/ *,TYPE_16__*) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (TYPE_12__*,int /*<<< orphan*/ *) ; 
 int mlx4_mtt_init (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx4_srq_alloc (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_11__* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_10__* to_mpd (struct ib_pd*) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 
 TYPE_9__* to_mxrcd (int /*<<< orphan*/ ) ; 

struct ib_srq *mlx4_ib_create_srq(struct ib_pd *pd,
				  struct ib_srq_init_attr *init_attr,
				  struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(pd->device);
	struct mlx4_ib_srq *srq;
	struct mlx4_wqe_srq_next_seg *next;
	struct mlx4_wqe_data_seg *scatter;
	u32 cqn;
	u16 xrcdn;
	int desc_size;
	int buf_size;
	int err;
	int i;

	/* Sanity check SRQ size before proceeding */
	if (init_attr->attr.max_wr  >= dev->dev->caps.max_srq_wqes ||
	    init_attr->attr.max_sge >  dev->dev->caps.max_srq_sge)
		return ERR_PTR(-EINVAL);

	srq = kmalloc(sizeof *srq, GFP_KERNEL);
	if (!srq)
		return ERR_PTR(-ENOMEM);

	mutex_init(&srq->mutex);
	spin_lock_init(&srq->lock);
	srq->msrq.max    = roundup_pow_of_two(init_attr->attr.max_wr + 1);
	srq->msrq.max_gs = init_attr->attr.max_sge;

	desc_size = max(32UL,
			roundup_pow_of_two(sizeof (struct mlx4_wqe_srq_next_seg) +
					   srq->msrq.max_gs *
					   sizeof (struct mlx4_wqe_data_seg)));
	srq->msrq.wqe_shift = ilog2(desc_size);

	buf_size = srq->msrq.max * desc_size;

	if (pd->uobject) {
		struct mlx4_ib_create_srq ucmd;

		if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd)) {
			err = -EFAULT;
			goto err_srq;
		}

		srq->umem = ib_umem_get(pd->uobject->context, ucmd.buf_addr,
					buf_size, 0, 0);
		if (IS_ERR(srq->umem)) {
			err = PTR_ERR(srq->umem);
			goto err_srq;
		}

		err = mlx4_mtt_init(dev->dev, ib_umem_page_count(srq->umem),
				    ilog2(srq->umem->page_size), &srq->mtt);
		if (err)
			goto err_buf;

		err = mlx4_ib_umem_write_mtt(dev, &srq->mtt, srq->umem);
		if (err)
			goto err_mtt;

		err = mlx4_ib_db_map_user(to_mucontext(pd->uobject->context),
					  ucmd.db_addr, &srq->db);
		if (err)
			goto err_mtt;
	} else {
		err = mlx4_db_alloc(dev->dev, &srq->db, 0);
		if (err)
			goto err_srq;

		*srq->db.db = 0;

		if (mlx4_buf_alloc(dev->dev, buf_size, PAGE_SIZE * 2, &srq->buf)) {
			err = -ENOMEM;
			goto err_db;
		}

		srq->head    = 0;
		srq->tail    = srq->msrq.max - 1;
		srq->wqe_ctr = 0;

		for (i = 0; i < srq->msrq.max; ++i) {
			next = get_wqe(srq, i);
			next->next_wqe_index =
				cpu_to_be16((i + 1) & (srq->msrq.max - 1));

			for (scatter = (void *) (next + 1);
			     (void *) scatter < (void *) next + desc_size;
			     ++scatter)
				scatter->lkey = cpu_to_be32(MLX4_INVALID_LKEY);
		}

		err = mlx4_mtt_init(dev->dev, srq->buf.npages, srq->buf.page_shift,
				    &srq->mtt);
		if (err)
			goto err_buf;

		err = mlx4_buf_write_mtt(dev->dev, &srq->mtt, &srq->buf);
		if (err)
			goto err_mtt;

		srq->wrid = kmalloc(srq->msrq.max * sizeof (u64), GFP_KERNEL);
		if (!srq->wrid) {
			err = -ENOMEM;
			goto err_mtt;
		}
	}

	cqn = (init_attr->srq_type == IB_SRQT_XRC) ?
		to_mcq(init_attr->ext.xrc.cq)->mcq.cqn : 0;
	xrcdn = (init_attr->srq_type == IB_SRQT_XRC) ?
		to_mxrcd(init_attr->ext.xrc.xrcd)->xrcdn :
		(u16) dev->dev->caps.reserved_xrcds;
	err = mlx4_srq_alloc(dev->dev, to_mpd(pd)->pdn, cqn, xrcdn, &srq->mtt,
			     srq->db.dma, &srq->msrq);
	if (err)
		goto err_wrid;

	srq->msrq.event = mlx4_ib_srq_event;
	srq->ibsrq.ext.xrc.srq_num = srq->msrq.srqn;

	if (pd->uobject)
		if (ib_copy_to_udata(udata, &srq->msrq.srqn, sizeof (__u32))) {
			err = -EFAULT;
			goto err_wrid;
		}

	init_attr->attr.max_wr = srq->msrq.max - 1;

	return &srq->ibsrq;

err_wrid:
	if (pd->uobject)
		mlx4_ib_db_unmap_user(to_mucontext(pd->uobject->context), &srq->db);
	else
		kfree(srq->wrid);

err_mtt:
	mlx4_mtt_cleanup(dev->dev, &srq->mtt);

err_buf:
	if (pd->uobject)
		ib_umem_release(srq->umem);
	else
		mlx4_buf_free(dev->dev, buf_size, &srq->buf);

err_db:
	if (!pd->uobject)
		mlx4_db_free(dev->dev, &srq->db);

err_srq:
	kfree(srq);

	return ERR_PTR(err);
}