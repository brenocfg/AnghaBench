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
struct nv50_bar_priv {int /*<<< orphan*/  lock; } ;
struct nouveau_bar {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wait (struct nv50_bar_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_warn (struct nv50_bar_priv*,char*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_bar_priv*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv50_bar_flush(struct nouveau_bar *bar)
{
	struct nv50_bar_priv *priv = (void *)bar;
	unsigned long flags;
	spin_lock_irqsave(&priv->lock, flags);
	nv_wr32(priv, 0x00330c, 0x00000001);
	if (!nv_wait(priv, 0x00330c, 0x00000002, 0x00000000))
		nv_warn(priv, "flush timeout\n");
	spin_unlock_irqrestore(&priv->lock, flags);
}