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
struct nvc0_ibus_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_error (struct nvc0_ibus_priv*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_ibus_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_rd32 (struct nvc0_ibus_priv*,int) ; 

__attribute__((used)) static void
nvc0_ibus_intr_rop(struct nvc0_ibus_priv *priv, int i)
{
	u32 addr = nv_rd32(priv, 0x124120 + (i * 0x0400));
	u32 data = nv_rd32(priv, 0x124124 + (i * 0x0400));
	u32 stat = nv_rd32(priv, 0x124128 + (i * 0x0400));
	nv_error(priv, "ROP%d: 0x%06x 0x%08x (0x%08x)\n", i, addr, data, stat);
	nv_mask(priv, 0x124128 + (i * 0x0400), 0x00000200, 0x00000000);
}