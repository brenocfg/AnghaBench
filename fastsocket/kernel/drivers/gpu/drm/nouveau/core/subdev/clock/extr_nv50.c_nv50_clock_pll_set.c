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
typedef  int /*<<< orphan*/  u32 ;
struct nvbios_pll {int type; int bias_p; scalar_t__ reg; } ;
struct nv50_clock_priv {int dummy; } ;
struct nouveau_clock {int dummy; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
#define  PLL_MEMORY 130 
#define  PLL_VPLL0 129 
#define  PLL_VPLL1 128 
 struct nouveau_bios* nouveau_bios (struct nv50_clock_priv*) ; 
 int nv04_pll_calc (struct nouveau_clock*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_clock*,char*,...) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_clock_priv*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_clock_priv*,scalar_t__,int) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 

__attribute__((used)) static int
nv50_clock_pll_set(struct nouveau_clock *clk, u32 type, u32 freq)
{
	struct nv50_clock_priv *priv = (void *)clk;
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_pll info;
	int N1, M1, N2, M2, P;
	int ret;

	ret = nvbios_pll_parse(bios, type, &info);
	if (ret) {
		nv_error(clk, "failed to retrieve pll data, %d\n", ret);
		return ret;
	}

	ret = nv04_pll_calc(clk, &info, freq, &N1, &M1, &N2, &M2, &P);
	if (!ret) {
		nv_error(clk, "failed pll calculation\n");
		return ret;
	}

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
		nv_wr32(priv, info.reg + 0, 0x10000611);
		nv_mask(priv, info.reg + 4, 0x00ff00ff, (M1 << 16) | N1);
		nv_mask(priv, info.reg + 8, 0x7fff00ff, (P  << 28) |
							(M2 << 16) | N2);
		break;
	case PLL_MEMORY:
		nv_mask(priv, info.reg + 0, 0x01ff0000, (P << 22) |
						        (info.bias_p << 19) |
							(P << 16));
		nv_wr32(priv, info.reg + 4, (N1 << 8) | M1);
		break;
	default:
		nv_mask(priv, info.reg + 0, 0x00070000, (P << 16));
		nv_wr32(priv, info.reg + 4, (N1 << 8) | M1);
		break;
	}

	return 0;
}