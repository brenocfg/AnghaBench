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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct TYPE_2__ {size_t token_mask; struct mlx4_cmd_context* context; } ;
struct mlx4_priv {TYPE_1__ cmd; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_context {size_t token; int /*<<< orphan*/  done; int /*<<< orphan*/  out_param; int /*<<< orphan*/  result; int /*<<< orphan*/  fw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_status_to_errno (int /*<<< orphan*/ ) ; 

void mlx4_cmd_event(struct mlx4_dev *dev, u16 token, u8 status, u64 out_param)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_cmd_context *context =
		&priv->cmd.context[token & priv->cmd.token_mask];

	/* previously timed out command completing at long last */
	if (token != context->token)
		return;

	context->fw_status = status;
	context->result    = mlx4_status_to_errno(status);
	context->out_param = out_param;

	complete(&context->done);
}