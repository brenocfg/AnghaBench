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
typedef  int u64 ;
typedef  int u32 ;
struct nv50_instobj_priv {TYPE_1__* mem; } ;
struct nv50_instmem_priv {int addr; int /*<<< orphan*/  lock; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nv50_instmem_priv*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
nv50_instobj_wr32(struct nouveau_object *object, u64 offset, u32 data)
{
	struct nv50_instmem_priv *priv = (void *)object->engine;
	struct nv50_instobj_priv *node = (void *)object;
	unsigned long flags;
	u64 base = (node->mem->offset + offset) & 0xffffff00000ULL;
	u64 addr = (node->mem->offset + offset) & 0x000000fffffULL;

	spin_lock_irqsave(&priv->lock, flags);
	if (unlikely(priv->addr != base)) {
		nv_wr32(priv, 0x001700, base >> 16);
		priv->addr = base;
	}
	nv_wr32(priv, 0x700000 + addr, data);
	spin_unlock_irqrestore(&priv->lock, flags);
}