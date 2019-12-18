#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int max; } ;
struct nv04_fifo_priv {TYPE_5__ base; TYPE_4__* ramfc; TYPE_3__* ramro; TYPE_2__* ramht; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_9__ {int addr; } ;
struct TYPE_8__ {int addr; } ;
struct TYPE_6__ {int addr; } ;
struct TYPE_7__ {int bits; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_PUSH0 ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHE1_PUSH1 ; 
 int /*<<< orphan*/  NV03_PFIFO_CACHES ; 
 int /*<<< orphan*/  NV03_PFIFO_INTR_0 ; 
 int /*<<< orphan*/  NV03_PFIFO_INTR_EN_0 ; 
 int /*<<< orphan*/  NV03_PFIFO_RAMFC ; 
 int /*<<< orphan*/  NV03_PFIFO_RAMHT ; 
 int /*<<< orphan*/  NV03_PFIFO_RAMRO ; 
 int /*<<< orphan*/  NV04_PFIFO_CACHE1_PULL0 ; 
 int /*<<< orphan*/  NV04_PFIFO_DELAY_0 ; 
 int /*<<< orphan*/  NV04_PFIFO_DMA_TIMESLICE ; 
 int nouveau_fifo_init (TYPE_5__*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_fifo_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv17_fifo_init(struct nouveau_object *object)
{
	struct nv04_fifo_priv *priv = (void *)object;
	int ret;

	ret = nouveau_fifo_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, NV04_PFIFO_DELAY_0, 0x000000ff);
	nv_wr32(priv, NV04_PFIFO_DMA_TIMESLICE, 0x0101ffff);

	nv_wr32(priv, NV03_PFIFO_RAMHT, (0x03 << 24) /* search 128 */ |
				       ((priv->ramht->bits - 9) << 16) |
				        (priv->ramht->base.addr >> 8));
	nv_wr32(priv, NV03_PFIFO_RAMRO, priv->ramro->addr >> 8);
	nv_wr32(priv, NV03_PFIFO_RAMFC, priv->ramfc->addr >> 8 | 0x00010000);

	nv_wr32(priv, NV03_PFIFO_CACHE1_PUSH1, priv->base.max);

	nv_wr32(priv, NV03_PFIFO_INTR_0, 0xffffffff);
	nv_wr32(priv, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nv_wr32(priv, NV03_PFIFO_CACHE1_PUSH0, 1);
	nv_wr32(priv, NV04_PFIFO_CACHE1_PULL0, 1);
	nv_wr32(priv, NV03_PFIFO_CACHES, 1);
	return 0;
}