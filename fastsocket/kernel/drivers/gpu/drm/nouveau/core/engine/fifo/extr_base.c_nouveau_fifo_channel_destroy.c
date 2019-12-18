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
struct nouveau_object {int dummy; } ;
struct nouveau_fifo_chan {size_t chid; int /*<<< orphan*/  base; int /*<<< orphan*/  pushdma; int /*<<< orphan*/  pushgpu; int /*<<< orphan*/  user; } ;
struct nouveau_fifo {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** channel; } ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_namedb_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 TYPE_1__* nv_object (struct nouveau_fifo_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nouveau_fifo_channel_destroy(struct nouveau_fifo_chan *chan)
{
	struct nouveau_fifo *priv = (void *)nv_object(chan)->engine;
	unsigned long flags;

	iounmap(chan->user);

	spin_lock_irqsave(&priv->lock, flags);
	priv->channel[chan->chid] = NULL;
	spin_unlock_irqrestore(&priv->lock, flags);

	nouveau_gpuobj_ref(NULL, &chan->pushgpu);
	nouveau_object_ref(NULL, (struct nouveau_object **)&chan->pushdma);
	nouveau_namedb_destroy(&chan->base);
}