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
struct mlx4_srq_context {int /*<<< orphan*/  limit_watermark; } ;
struct mlx4_srq {int /*<<< orphan*/  srqn; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {struct mlx4_srq_context* buf; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int mlx4_QUERY_SRQ (struct mlx4_dev*,struct mlx4_cmd_mailbox*,int /*<<< orphan*/ ) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_srq_query(struct mlx4_dev *dev, struct mlx4_srq *srq, int *limit_watermark)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_srq_context *srq_context;
	int err;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	srq_context = mailbox->buf;

	err = mlx4_QUERY_SRQ(dev, mailbox, srq->srqn);
	if (err)
		goto err_out;
	*limit_watermark = be16_to_cpu(srq_context->limit_watermark);

err_out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}