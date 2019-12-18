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
struct nv50_disp_priv {int dummy; } ;
struct nouveau_clock {int /*<<< orphan*/  (* pll_set ) (struct nouveau_clock*,scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ PLL_VPLL0 ; 
 struct nouveau_clock* nouveau_clock (struct nv50_disp_priv*) ; 
 int nv_rd32 (struct nv50_disp_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_disp_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_clock*,scalar_t__,int) ; 

__attribute__((used)) static void
nvd0_disp_intr_unk2_1(struct nv50_disp_priv *priv, int head)
{
	struct nouveau_clock *clk = nouveau_clock(priv);
	u32 pclk = nv_rd32(priv, 0x660450 + (head * 0x300)) / 1000;
	if (pclk)
		clk->pll_set(clk, PLL_VPLL0 + head, pclk);
	nv_wr32(priv, 0x612200 + (head * 0x800), 0x00000000);
}