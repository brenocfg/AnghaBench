#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_resize_cq {int /*<<< orphan*/  buf_addr; } ;
struct mlx4_ib_dev {int dummy; } ;
struct mlx4_ib_cq {TYPE_2__* resize_buf; scalar_t__ resize_umem; TYPE_1__* umem; } ;
struct ib_udata {int dummy; } ;
struct TYPE_5__ {int cqe; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ ib_copy_from_udata (struct mlx4_ib_resize_cq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_ib_get_cq_umem (struct mlx4_ib_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlx4_alloc_resize_umem(struct mlx4_ib_dev *dev, struct mlx4_ib_cq *cq,
				   int entries, struct ib_udata *udata)
{
	struct mlx4_ib_resize_cq ucmd;
	int err;

	if (cq->resize_umem)
		return -EBUSY;

	if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd))
		return -EFAULT;

	cq->resize_buf = kmalloc(sizeof *cq->resize_buf, GFP_ATOMIC);
	if (!cq->resize_buf)
		return -ENOMEM;

	err = mlx4_ib_get_cq_umem(dev, cq->umem->context, &cq->resize_buf->buf,
				  &cq->resize_umem, ucmd.buf_addr, entries);
	if (err) {
		kfree(cq->resize_buf);
		cq->resize_buf = NULL;
		return err;
	}

	cq->resize_buf->cqe = entries - 1;

	return 0;
}