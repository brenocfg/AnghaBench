#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx4_ib_dev {int dummy; } ;
struct mlx4_ib_cq {TYPE_1__* resize_buf; } ;
struct TYPE_3__ {int cqe; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_ib_alloc_cq_buf (struct mlx4_ib_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx4_alloc_resize_buf(struct mlx4_ib_dev *dev, struct mlx4_ib_cq *cq,
				  int entries)
{
	int err;

	if (cq->resize_buf)
		return -EBUSY;

	cq->resize_buf = kmalloc(sizeof *cq->resize_buf, GFP_ATOMIC);
	if (!cq->resize_buf)
		return -ENOMEM;

	err = mlx4_ib_alloc_cq_buf(dev, &cq->resize_buf->buf, entries);
	if (err) {
		kfree(cq->resize_buf);
		cq->resize_buf = NULL;
		return err;
	}

	cq->resize_buf->cqe = entries - 1;

	return 0;
}