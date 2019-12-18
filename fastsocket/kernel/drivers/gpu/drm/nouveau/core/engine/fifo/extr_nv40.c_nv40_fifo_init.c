#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int max; } ;
struct nv04_fifo_priv {TYPE_7__ base; TYPE_5__* ramfc; TYPE_3__* ramro; TYPE_2__* ramht; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct nouveau_fb {TYPE_4__ ram; } ;
struct TYPE_13__ {int chipset; } ;
struct TYPE_12__ {int addr; } ;
struct TYPE_10__ {int addr; } ;
struct TYPE_8__ {int addr; } ;
struct TYPE_9__ {int bits; TYPE_1__ base; } ;

/* Variables and functions */
 int NV03_PFIFO_CACHE1_PUSH0 ; 
 int NV03_PFIFO_CACHE1_PUSH1 ; 
 int NV03_PFIFO_CACHES ; 
 int NV03_PFIFO_INTR_0 ; 
 int NV03_PFIFO_INTR_EN_0 ; 
 int NV03_PFIFO_RAMHT ; 
 int NV03_PFIFO_RAMRO ; 
 int NV04_PFIFO_CACHE1_PULL0 ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int nouveau_fifo_init (TYPE_7__*) ; 
 TYPE_6__* nv_device (struct nv04_fifo_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_fifo_priv*,int,int) ; 

__attribute__((used)) static int
nv40_fifo_init(struct nouveau_object *object)
{
	struct nv04_fifo_priv *priv = (void *)object;
	struct nouveau_fb *pfb = nouveau_fb(object);
	int ret;

	ret = nouveau_fifo_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x002040, 0x000000ff);
	nv_wr32(priv, 0x002044, 0x2101ffff);
	nv_wr32(priv, 0x002058, 0x00000001);

	nv_wr32(priv, NV03_PFIFO_RAMHT, (0x03 << 24) /* search 128 */ |
				       ((priv->ramht->bits - 9) << 16) |
				        (priv->ramht->base.addr >> 8));
	nv_wr32(priv, NV03_PFIFO_RAMRO, priv->ramro->addr >> 8);

	switch (nv_device(priv)->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		nv_wr32(priv, 0x002230, 0x00000001);
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x48:
		nv_wr32(priv, 0x002220, 0x00030002);
		break;
	default:
		nv_wr32(priv, 0x002230, 0x00000000);
		nv_wr32(priv, 0x002220, ((pfb->ram.size - 512 * 1024 +
					 priv->ramfc->addr) >> 16) |
					0x00030000);
		break;
	}

	nv_wr32(priv, NV03_PFIFO_CACHE1_PUSH1, priv->base.max);

	nv_wr32(priv, NV03_PFIFO_INTR_0, 0xffffffff);
	nv_wr32(priv, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nv_wr32(priv, NV03_PFIFO_CACHE1_PUSH0, 1);
	nv_wr32(priv, NV04_PFIFO_CACHE1_PULL0, 1);
	nv_wr32(priv, NV03_PFIFO_CACHES, 1);
	return 0;
}