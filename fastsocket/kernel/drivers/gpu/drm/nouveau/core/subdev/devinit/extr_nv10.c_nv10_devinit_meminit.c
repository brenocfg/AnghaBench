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
typedef  int uint32_t ;
struct nv10_devinit_priv {int dummy; } ;
struct nouveau_devinit {int dummy; } ;
struct io_mapping {int dummy; } ;
struct TYPE_2__ {int chipset; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV04_PFB_CFG0 ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL ; 
 int /*<<< orphan*/  NV10_PFB_REFCTRL_VALID_1 ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (int /*<<< orphan*/ ) ; 
 int fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,int) ; 
 TYPE_1__* nv_device (struct nv10_devinit_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nv10_devinit_priv*,char*) ; 
 int /*<<< orphan*/  nv_mask (struct nv10_devinit_priv*,int /*<<< orphan*/ ,int,int const) ; 
 int nv_rd32 (struct nv10_devinit_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_devinit_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv10_devinit_meminit(struct nouveau_devinit *devinit)
{
	struct nv10_devinit_priv *priv = (void *)devinit;
	const int mem_width[] = { 0x10, 0x00, 0x20 };
	const int mem_width_count = nv_device(priv)->chipset >= 0x17 ? 3 : 2;
	uint32_t patt = 0xdeadbeef;
	struct io_mapping *fb;
	int i, j, k;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	nv_wr32(priv, NV10_PFB_REFCTRL, NV10_PFB_REFCTRL_VALID_1);

	/* Probe memory bus width */
	for (i = 0; i < mem_width_count; i++) {
		nv_mask(priv, NV04_PFB_CFG0, 0x30, mem_width[i]);

		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++)
				fbmem_poke(fb, 0x1c, 0);

			fbmem_poke(fb, 0x1c, patt);
			fbmem_poke(fb, 0x3c, 0);

			if (fbmem_peek(fb, 0x1c) == patt)
				goto mem_width_found;
		}
	}

mem_width_found:
	patt <<= 1;

	/* Probe amount of installed memory */
	for (i = 0; i < 4; i++) {
		int off = nv_rd32(priv, 0x10020c) - 0x100000;

		fbmem_poke(fb, off, patt);
		fbmem_poke(fb, 0, 0);

		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);
		fbmem_peek(fb, 0);

		if (fbmem_peek(fb, off) == patt)
			goto amount_found;
	}

	/* IC missing - disable the upper half memory space. */
	nv_mask(priv, NV04_PFB_CFG0, 0x1000, 0);

amount_found:
	fbmem_fini(fb);
}