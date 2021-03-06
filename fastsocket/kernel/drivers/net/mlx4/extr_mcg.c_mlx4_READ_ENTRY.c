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
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_READ_MCG ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_READ_ENTRY(struct mlx4_dev *dev, int index,
			   struct mlx4_cmd_mailbox *mailbox)
{
	return mlx4_cmd_box(dev, 0, mailbox->dma, index, 0, MLX4_CMD_READ_MCG,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
}