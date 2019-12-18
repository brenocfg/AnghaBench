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
typedef  int uint32_t ;
struct nv20_devinit_priv {int dummy; } ;
struct nouveau_devinit {int dummy; } ;
struct nouveau_device {int chipset; int /*<<< orphan*/  pdev; } ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL_VALID_1 ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (int /*<<< orphan*/ ) ; 
 int fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,int) ; 
 struct nouveau_device* nv_device (struct nv20_devinit_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nv20_devinit_priv*,char*) ; 
 int /*<<< orphan*/  nv_mask (struct nv20_devinit_priv*,int /*<<< orphan*/ ,int,int) ; 
 int nv_rd32 (struct nv20_devinit_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv20_devinit_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv20_devinit_meminit(struct nouveau_devinit *devinit)
{
	struct nv20_devinit_priv *priv = (void *)devinit;
	struct nouveau_device *device = nv_device(priv);
	uint32_t mask = (device->chipset >= 0x25 ? 0x300 : 0x900);
	uint32_t amount, off;
	struct io_mapping *fb;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	nv_wr32(priv, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Allow full addressing */
	nv_mask(priv, NV04_PFB_CFG0, 0, mask);

	amount = nv_rd32(priv, 0x10020c);
	for (off = amount; off > 0x2000000; off -= 0x2000000)
		fbmem_poke(fb, off - 4, off);

	amount = nv_rd32(priv, 0x10020c);
	if (amount != fbmem_peek(fb, amount - 4))
		/* IC missing - disable the upper half memory space. */
		nv_mask(priv, NV04_PFB_CFG0, mask, 0);

	fbmem_fini(fb);
}