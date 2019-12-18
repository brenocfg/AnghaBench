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
struct nvc0_ltcg_priv {int subp_nr; } ;
struct nouveau_subdev {int dummy; } ;

/* Variables and functions */
 int ffs (int) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_ltcg_priv*,int,int,int) ; 
 int nv_rd32 (struct nvc0_ltcg_priv*,int) ; 
 int /*<<< orphan*/  nvc0_ltcg_subp_isr (struct nvc0_ltcg_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_ltcg_intr(struct nouveau_subdev *subdev)
{
	struct nvc0_ltcg_priv *priv = (void *)subdev;
	u32 units;

	units = nv_rd32(priv, 0x00017c);
	while (units) {
		u32 subp, unit = ffs(units) - 1;
		for (subp = 0; subp < priv->subp_nr; subp++)
			nvc0_ltcg_subp_isr(priv, unit, subp);
		units &= ~(1 << unit);
	}

	/* we do something horribly wrong and upset PMFB a lot, so mask off
	 * interrupts from it after the first one until it's fixed
	 */
	nv_mask(priv, 0x000640, 0x02000000, 0x00000000);
}