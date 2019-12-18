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
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct mlx4_ib_cq_buf {int entry_size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_buf_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_ib_free_cq_buf(struct mlx4_ib_dev *dev, struct mlx4_ib_cq_buf *buf, int cqe)
{
	mlx4_buf_free(dev->dev, (cqe + 1) * buf->entry_size, &buf->buf);
}