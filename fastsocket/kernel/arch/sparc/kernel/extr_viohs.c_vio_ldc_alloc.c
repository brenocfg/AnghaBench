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
struct vio_driver_state {struct ldc_channel* lp; TYPE_1__* vdev; } ;
struct ldc_channel_config {int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;
struct ldc_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel_id; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ldc_channel*) ; 
 int PTR_ERR (struct ldc_channel*) ; 
 struct ldc_channel* ldc_alloc (int /*<<< orphan*/ ,struct ldc_channel_config*,void*) ; 

int vio_ldc_alloc(struct vio_driver_state *vio,
			 struct ldc_channel_config *base_cfg,
			 void *event_arg)
{
	struct ldc_channel_config cfg = *base_cfg;
	struct ldc_channel *lp;

	cfg.tx_irq = vio->vdev->tx_irq;
	cfg.rx_irq = vio->vdev->rx_irq;

	lp = ldc_alloc(vio->vdev->channel_id, &cfg, event_arg);
	if (IS_ERR(lp))
		return PTR_ERR(lp);

	vio->lp = lp;

	return 0;
}