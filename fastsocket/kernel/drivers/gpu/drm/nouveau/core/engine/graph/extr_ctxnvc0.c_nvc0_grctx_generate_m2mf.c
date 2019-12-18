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
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_grctx_generate_m2mf(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x404604, 0x00000015);
	nv_wr32(priv, 0x404608, 0x00000000);
	nv_wr32(priv, 0x40460c, 0x00002e00);
	nv_wr32(priv, 0x404610, 0x00000100);
	nv_wr32(priv, 0x404618, 0x00000000);
	nv_wr32(priv, 0x40461c, 0x00000000);
	nv_wr32(priv, 0x404620, 0x00000000);
	nv_wr32(priv, 0x404624, 0x00000000);
	nv_wr32(priv, 0x404628, 0x00000000);
	nv_wr32(priv, 0x40462c, 0x00000000);
	nv_wr32(priv, 0x404630, 0x00000000);
	nv_wr32(priv, 0x404634, 0x00000000);
	nv_wr32(priv, 0x404638, 0x00000004);
	nv_wr32(priv, 0x40463c, 0x00000000);
	nv_wr32(priv, 0x404640, 0x00000000);
	nv_wr32(priv, 0x404644, 0x00000000);
	nv_wr32(priv, 0x404648, 0x00000000);
	nv_wr32(priv, 0x40464c, 0x00000000);
	nv_wr32(priv, 0x404650, 0x00000000);
	nv_wr32(priv, 0x404654, 0x00000000);
	nv_wr32(priv, 0x404658, 0x00000000);
	nv_wr32(priv, 0x40465c, 0x007f0100);
	nv_wr32(priv, 0x404660, 0x00000000);
	nv_wr32(priv, 0x404664, 0x00000000);
	nv_wr32(priv, 0x404668, 0x00000000);
	nv_wr32(priv, 0x40466c, 0x00000000);
	nv_wr32(priv, 0x404670, 0x00000000);
	nv_wr32(priv, 0x404674, 0x00000000);
	nv_wr32(priv, 0x404678, 0x00000000);
	nv_wr32(priv, 0x40467c, 0x00000002);
	nv_wr32(priv, 0x404680, 0x00000000);
	nv_wr32(priv, 0x404684, 0x00000000);
	nv_wr32(priv, 0x404688, 0x00000000);
	nv_wr32(priv, 0x40468c, 0x00000000);
	nv_wr32(priv, 0x404690, 0x00000000);
	nv_wr32(priv, 0x404694, 0x00000000);
	nv_wr32(priv, 0x404698, 0x00000000);
	nv_wr32(priv, 0x40469c, 0x00000000);
	nv_wr32(priv, 0x4046a0, 0x007f0080);
	nv_wr32(priv, 0x4046a4, 0x00000000);
	nv_wr32(priv, 0x4046a8, 0x00000000);
	nv_wr32(priv, 0x4046ac, 0x00000000);
	nv_wr32(priv, 0x4046b0, 0x00000000);
	nv_wr32(priv, 0x4046b4, 0x00000000);
	nv_wr32(priv, 0x4046b8, 0x00000000);
	nv_wr32(priv, 0x4046bc, 0x00000000);
	nv_wr32(priv, 0x4046c0, 0x00000000);
	nv_wr32(priv, 0x4046c4, 0x00000000);
	nv_wr32(priv, 0x4046c8, 0x00000000);
	nv_wr32(priv, 0x4046cc, 0x00000000);
	nv_wr32(priv, 0x4046d0, 0x00000000);
	nv_wr32(priv, 0x4046d4, 0x00000000);
	nv_wr32(priv, 0x4046d8, 0x00000000);
	nv_wr32(priv, 0x4046dc, 0x00000000);
	nv_wr32(priv, 0x4046e0, 0x00000000);
	nv_wr32(priv, 0x4046e4, 0x00000000);
	nv_wr32(priv, 0x4046e8, 0x00000000);
	nv_wr32(priv, 0x4046f0, 0x00000000);
	nv_wr32(priv, 0x4046f4, 0x00000000);
}