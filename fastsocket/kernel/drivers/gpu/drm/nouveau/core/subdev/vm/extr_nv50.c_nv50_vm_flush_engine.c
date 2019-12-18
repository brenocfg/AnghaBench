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
struct nv50_vmmgr_priv {int /*<<< orphan*/  lock; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ nouveau_vmmgr (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_subdev*,char*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nouveau_subdev*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nouveau_subdev*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
nv50_vm_flush_engine(struct nouveau_subdev *subdev, int engine)
{
	struct nv50_vmmgr_priv *priv = (void *)nouveau_vmmgr(subdev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	nv_wr32(subdev, 0x100c80, (engine << 16) | 1);
	if (!nv_wait(subdev, 0x100c80, 0x00000001, 0x00000000))
		nv_error(subdev, "vm flush timeout: engine %d\n", engine);
	spin_unlock_irqrestore(&priv->lock, flags);
}