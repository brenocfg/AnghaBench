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
typedef  int u32 ;
struct nv31_mpeg_priv {int dummy; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct nouveau_instmem {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_instmem* nouveau_instmem (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_mask (struct nv31_mpeg_priv*,int,int,int) ; 
 int nv_ro32 (struct nouveau_instmem*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv31_mpeg_priv*,int,int) ; 

__attribute__((used)) static int
nv31_mpeg_mthd_dma(struct nouveau_object *object, u32 mthd, void *arg, u32 len)
{
	struct nouveau_instmem *imem = nouveau_instmem(object);
	struct nv31_mpeg_priv *priv = (void *)object->engine;
	u32 inst = *(u32 *)arg << 4;
	u32 dma0 = nv_ro32(imem, inst + 0);
	u32 dma1 = nv_ro32(imem, inst + 4);
	u32 dma2 = nv_ro32(imem, inst + 8);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;

	/* only allow linear DMA objects */
	if (!(dma0 & 0x00002000))
		return -EINVAL;

	if (mthd == 0x0190) {
		/* DMA_CMD */
		nv_mask(priv, 0x00b300, 0x00030000, (dma0 & 0x00030000));
		nv_wr32(priv, 0x00b334, base);
		nv_wr32(priv, 0x00b324, size);
	} else
	if (mthd == 0x01a0) {
		/* DMA_DATA */
		nv_mask(priv, 0x00b300, 0x000c0000, (dma0 & 0x00030000) << 2);
		nv_wr32(priv, 0x00b360, base);
		nv_wr32(priv, 0x00b364, size);
	} else {
		/* DMA_IMAGE, VRAM only */
		if (dma0 & 0x000c0000)
			return -EINVAL;

		nv_wr32(priv, 0x00b370, base);
		nv_wr32(priv, 0x00b374, size);
	}

	return 0;
}