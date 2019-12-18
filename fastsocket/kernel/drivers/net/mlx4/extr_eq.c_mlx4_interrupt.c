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
struct TYPE_3__ {int /*<<< orphan*/ * eq; int /*<<< orphan*/  clr_int; int /*<<< orphan*/  clr_mask; } ;
struct mlx4_priv {TYPE_1__ eq_table; } ;
struct TYPE_4__ {int num_comp_vectors; } ;
struct mlx4_dev {TYPE_2__ caps; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int mlx4_eq_int (struct mlx4_dev*,int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mlx4_interrupt(int irq, void *dev_ptr)
{
	struct mlx4_dev *dev = dev_ptr;
	struct mlx4_priv *priv = mlx4_priv(dev);
	int work = 0;
	int i;

	writel(priv->eq_table.clr_mask, priv->eq_table.clr_int);

	for (i = 0; i < dev->caps.num_comp_vectors + 1; ++i)
		work |= mlx4_eq_int(dev, &priv->eq_table.eq[i]);

	return IRQ_RETVAL(work);
}