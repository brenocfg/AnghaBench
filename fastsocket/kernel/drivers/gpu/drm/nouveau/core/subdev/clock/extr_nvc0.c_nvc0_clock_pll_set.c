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
struct nvc0_clock_priv {int dummy; } ;
struct nvbios_pll {int type; int /*<<< orphan*/  reg; } ;
struct nouveau_clock {int dummy; } ;
struct nouveau_bios {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_VPLL0 131 
#define  PLL_VPLL1 130 
#define  PLL_VPLL2 129 
#define  PLL_VPLL3 128 
 struct nouveau_bios* nouveau_bios (struct nvc0_clock_priv*) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_clock_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_warn (struct nvc0_clock_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_clock_priv*,int /*<<< orphan*/ ,int) ; 
 int nva3_pll_calc (struct nouveau_clock*,struct nvbios_pll*,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int nvbios_pll_parse (struct nouveau_bios*,int /*<<< orphan*/ ,struct nvbios_pll*) ; 

__attribute__((used)) static int
nvc0_clock_pll_set(struct nouveau_clock *clk, u32 type, u32 freq)
{
	struct nvc0_clock_priv *priv = (void *)clk;
	struct nouveau_bios *bios = nouveau_bios(priv);
	struct nvbios_pll info;
	int N, fN, M, P;
	int ret;

	ret = nvbios_pll_parse(bios, type, &info);
	if (ret)
		return ret;

	ret = nva3_pll_calc(clk, &info, freq, &N, &fN, &M, &P);
	if (ret < 0)
		return ret;

	switch (info.type) {
	case PLL_VPLL0:
	case PLL_VPLL1:
	case PLL_VPLL2:
	case PLL_VPLL3:
		nv_mask(priv, info.reg + 0x0c, 0x00000000, 0x00000100);
		nv_wr32(priv, info.reg + 0x04, (P << 16) | (N << 8) | M);
		nv_wr32(priv, info.reg + 0x10, fN << 16);
		break;
	default:
		nv_warn(priv, "0x%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		break;
	}

	return ret;
}