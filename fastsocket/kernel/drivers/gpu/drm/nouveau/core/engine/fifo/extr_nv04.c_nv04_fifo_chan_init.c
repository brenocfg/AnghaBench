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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct nv04_fifo_priv {TYPE_1__ base; } ;
struct TYPE_4__ {int chid; } ;
struct nv04_fifo_chan {TYPE_2__ base; } ;
struct nouveau_object {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFIFO_MODE ; 
 int nouveau_fifo_channel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_fifo_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nv04_fifo_chan_init(struct nouveau_object *object)
{
	struct nv04_fifo_priv *priv = (void *)object->engine;
	struct nv04_fifo_chan *chan = (void *)object;
	u32 mask = 1 << chan->base.chid;
	unsigned long flags;
	int ret;

	ret = nouveau_fifo_channel_init(&chan->base);
	if (ret)
		return ret;

	spin_lock_irqsave(&priv->base.lock, flags);
	nv_mask(priv, NV04_PFIFO_MODE, mask, mask);
	spin_unlock_irqrestore(&priv->base.lock, flags);
	return 0;
}