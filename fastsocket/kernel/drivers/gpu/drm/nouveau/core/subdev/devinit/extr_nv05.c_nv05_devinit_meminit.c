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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct nv05_devinit_priv {int dummy; } ;
struct nouveau_devinit {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct io_mapping {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int NV04_PFB_BOOT_0 ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_16MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_32MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_4MB ; 
 int NV04_PFB_BOOT_0_RAM_AMOUNT_8MB ; 
 int NV04_PFB_BOOT_0_RAM_WIDTH_128 ; 
 int NV04_PFB_BOOT_0_UMA_ENABLE ; 
 int NV04_PFB_CFG0 ; 
 int NV04_PFB_CFG0_SCRAMBLE ; 
 int NV04_PFB_CFG1 ; 
 int NV04_PFB_DEBUG_0 ; 
 int NV04_PFB_DEBUG_0_REFRESH_OFF ; 
 int /*<<< orphan*/  NV04_PFB_SCRAMBLE (int) ; 
 scalar_t__ bmp_mem_init_table (struct nouveau_bios*) ; 
 int /*<<< orphan*/  fbmem_fini (struct io_mapping*) ; 
 struct io_mapping* fbmem_init (int /*<<< orphan*/ ) ; 
 scalar_t__ fbmem_peek (struct io_mapping*,int) ; 
 int /*<<< orphan*/  fbmem_poke (struct io_mapping*,int,scalar_t__) ; 
 int /*<<< orphan*/  fbmem_readback (struct io_mapping*,int,scalar_t__) ; 
 struct nouveau_bios* nouveau_bios (struct nv05_devinit_priv*) ; 
 TYPE_1__* nv_device (struct nv05_devinit_priv*) ; 
 int /*<<< orphan*/  nv_error (struct nv05_devinit_priv*,char*) ; 
 int /*<<< orphan*/  nv_mask (struct nv05_devinit_priv*,int,int,int) ; 
 int nv_rd32 (struct nv05_devinit_priv*,int) ; 
 int nv_rdvgas (struct nv05_devinit_priv*,int /*<<< orphan*/ ,int) ; 
 int nv_ro08 (struct nouveau_bios*,scalar_t__) ; 
 scalar_t__ nv_ro32 (struct nouveau_bios*,scalar_t__) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv05_devinit_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nv_wrvgas (struct nv05_devinit_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
nv05_devinit_meminit(struct nouveau_devinit *devinit)
{
	static const u8 default_config_tab[][2] = {
		{ 0x24, 0x00 },
		{ 0x28, 0x00 },
		{ 0x24, 0x01 },
		{ 0x1f, 0x00 },
		{ 0x0f, 0x00 },
		{ 0x17, 0x00 },
		{ 0x06, 0x00 },
		{ 0x00, 0x00 }
	};
	struct nv05_devinit_priv *priv = (void *)devinit;
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct io_mapping *fb;
	u32 patt = 0xdeadbeef;
	u16 data;
	u8 strap, ramcfg[2];
	int i, v;

	/* Map the framebuffer aperture */
	fb = fbmem_init(nv_device(priv)->pdev);
	if (!fb) {
		nv_error(priv, "failed to map fb\n");
		return;
	}

	strap = (nv_rd32(priv, 0x101000) & 0x0000003c) >> 2;
	if ((data = bmp_mem_init_table(bios))) {
		ramcfg[0] = nv_ro08(bios, data + 2 * strap + 0);
		ramcfg[1] = nv_ro08(bios, data + 2 * strap + 1);
	} else {
		ramcfg[0] = default_config_tab[strap][0];
		ramcfg[1] = default_config_tab[strap][1];
	}

	/* Sequencer off */
	nv_wrvgas(priv, 0, 1, nv_rdvgas(priv, 0, 1) | 0x20);

	if (nv_rd32(priv, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_UMA_ENABLE)
		goto out;

	nv_mask(priv, NV04_PFB_DEBUG_0, NV04_PFB_DEBUG_0_REFRESH_OFF, 0);

	/* If present load the hardcoded scrambling table */
	if (data) {
		for (i = 0, data += 0x10; i < 8; i++, data += 4) {
			u32 scramble = nv_ro32(bios, data);
			nv_wr32(priv, NV04_PFB_SCRAMBLE(i), scramble);
		}
	}

	/* Set memory type/width/length defaults depending on the straps */
	nv_mask(priv, NV04_PFB_BOOT_0, 0x3f, ramcfg[0]);

	if (ramcfg[1] & 0x80)
		nv_mask(priv, NV04_PFB_CFG0, 0, NV04_PFB_CFG0_SCRAMBLE);

	nv_mask(priv, NV04_PFB_CFG1, 0x700001, (ramcfg[1] & 1) << 20);
	nv_mask(priv, NV04_PFB_CFG1, 0, 1);

	/* Probe memory bus width */
	for (i = 0; i < 4; i++)
		fbmem_poke(fb, 4 * i, patt);

	if (fbmem_peek(fb, 0xc) != patt)
		nv_mask(priv, NV04_PFB_BOOT_0,
			  NV04_PFB_BOOT_0_RAM_WIDTH_128, 0);

	/* Probe memory length */
	v = nv_rd32(priv, NV04_PFB_BOOT_0) & NV04_PFB_BOOT_0_RAM_AMOUNT;

	if (v == NV04_PFB_BOOT_0_RAM_AMOUNT_32MB &&
	    (!fbmem_readback(fb, 0x1000000, ++patt) ||
	     !fbmem_readback(fb, 0, ++patt)))
		nv_mask(priv, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_16MB);

	if (v == NV04_PFB_BOOT_0_RAM_AMOUNT_16MB &&
	    !fbmem_readback(fb, 0x800000, ++patt))
		nv_mask(priv, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_8MB);

	if (!fbmem_readback(fb, 0x400000, ++patt))
		nv_mask(priv, NV04_PFB_BOOT_0, NV04_PFB_BOOT_0_RAM_AMOUNT,
			  NV04_PFB_BOOT_0_RAM_AMOUNT_4MB);

out:
	/* Sequencer on */
	nv_wrvgas(priv, 0, 1, nv_rdvgas(priv, 0, 1) & ~0x20);
	fbmem_fini(fb);
}