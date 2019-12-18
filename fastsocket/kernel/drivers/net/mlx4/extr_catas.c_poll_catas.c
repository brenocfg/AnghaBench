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
struct TYPE_2__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  list; int /*<<< orphan*/  map; } ;
struct mlx4_priv {TYPE_1__ catas_err; } ;
struct mlx4_dev {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 scalar_t__ MLX4_CATAS_POLL_INTERVAL ; 
 int /*<<< orphan*/  MLX4_DEV_EVENT_CATASTROPHIC_ERROR ; 
 int /*<<< orphan*/  catas_list ; 
 int /*<<< orphan*/  catas_lock ; 
 int /*<<< orphan*/  catas_work ; 
 int /*<<< orphan*/  dump_err_buf (struct mlx4_dev*) ; 
 scalar_t__ internal_err_reset ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_dispatch_event (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_wq ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poll_catas(unsigned long dev_ptr)
{
	struct mlx4_dev *dev = (struct mlx4_dev *) dev_ptr;
	struct mlx4_priv *priv = mlx4_priv(dev);

	if (readl(priv->catas_err.map)) {
		/* If the device is off-line, we cannot try to recover it */
		if (pci_channel_offline(dev->pdev))
			mod_timer(&priv->catas_err.timer,
				  round_jiffies(jiffies + MLX4_CATAS_POLL_INTERVAL));
		else {
			dump_err_buf(dev);
			mlx4_dispatch_event(dev, MLX4_DEV_EVENT_CATASTROPHIC_ERROR, 0);

			if (internal_err_reset) {
				spin_lock(&catas_lock);
				list_add(&priv->catas_err.list, &catas_list);
				spin_unlock(&catas_lock);

				queue_work(mlx4_wq, &catas_work);
			}
		}
	} else
		mod_timer(&priv->catas_err.timer,
			  round_jiffies(jiffies + MLX4_CATAS_POLL_INTERVAL));
}