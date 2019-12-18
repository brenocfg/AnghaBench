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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u32 ;
struct nvbios_pll {int bias_p; int max_p; } ;
struct nv04_clock_priv {int dummy; } ;
struct nouveau_pll_vals {int NM2; int NM1; int log2P; scalar_t__ N2; scalar_t__ M2; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bios (struct nv04_clock_priv*) ; 
 int nv_rd32 (struct nv04_clock_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_clock_priv*,int,int) ; 
 scalar_t__ nvbios_pll_parse (int /*<<< orphan*/ ,int,struct nvbios_pll*) ; 

__attribute__((used)) static void
setPLL_double_lowregs(struct nv04_clock_priv *priv, u32 NMNMreg,
		      struct nouveau_pll_vals *pv)
{
	/* When setting PLLs, there is a merry game of disabling and enabling
	 * various bits of hardware during the process. This function is a
	 * synthesis of six nv4x traces, nearly each card doing a subtly
	 * different thing. With luck all the necessary bits for each card are
	 * combined herein. Without luck it deviates from each card's formula
	 * so as to not work on any :)
	 */

	uint32_t Preg = NMNMreg - 4;
	bool mpll = Preg == 0x4020;
	uint32_t oldPval = nv_rd32(priv, Preg);
	uint32_t NMNM = pv->NM2 << 16 | pv->NM1;
	uint32_t Pval = (oldPval & (mpll ? ~(0x77 << 16) : ~(7 << 16))) |
			0xc << 28 | pv->log2P << 16;
	uint32_t saved4600 = 0;
	/* some cards have different maskc040s */
	uint32_t maskc040 = ~(3 << 14), savedc040;
	bool single_stage = !pv->NM2 || pv->N2 == pv->M2;

	if (nv_rd32(priv, NMNMreg) == NMNM && (oldPval & 0xc0070000) == Pval)
		return;

	if (Preg == 0x4000)
		maskc040 = ~0x333;
	if (Preg == 0x4058)
		maskc040 = ~(0xc << 24);

	if (mpll) {
		struct nvbios_pll info;
		uint8_t Pval2;

		if (nvbios_pll_parse(nouveau_bios(priv), Preg, &info))
			return;

		Pval2 = pv->log2P + info.bias_p;
		if (Pval2 > info.max_p)
			Pval2 = info.max_p;
		Pval |= 1 << 28 | Pval2 << 20;

		saved4600 = nv_rd32(priv, 0x4600);
		nv_wr32(priv, 0x4600, saved4600 | 8 << 28);
	}
	if (single_stage)
		Pval |= mpll ? 1 << 12 : 1 << 8;

	nv_wr32(priv, Preg, oldPval | 1 << 28);
	nv_wr32(priv, Preg, Pval & ~(4 << 28));
	if (mpll) {
		Pval |= 8 << 20;
		nv_wr32(priv, 0x4020, Pval & ~(0xc << 28));
		nv_wr32(priv, 0x4038, Pval & ~(0xc << 28));
	}

	savedc040 = nv_rd32(priv, 0xc040);
	nv_wr32(priv, 0xc040, savedc040 & maskc040);

	nv_wr32(priv, NMNMreg, NMNM);
	if (NMNMreg == 0x4024)
		nv_wr32(priv, 0x403c, NMNM);

	nv_wr32(priv, Preg, Pval);
	if (mpll) {
		Pval &= ~(8 << 20);
		nv_wr32(priv, 0x4020, Pval);
		nv_wr32(priv, 0x4038, Pval);
		nv_wr32(priv, 0x4600, saved4600);
	}

	nv_wr32(priv, 0xc040, savedc040);

	if (mpll) {
		nv_wr32(priv, 0x4020, Pval & ~(1 << 28));
		nv_wr32(priv, 0x4038, Pval & ~(1 << 28));
	}
}