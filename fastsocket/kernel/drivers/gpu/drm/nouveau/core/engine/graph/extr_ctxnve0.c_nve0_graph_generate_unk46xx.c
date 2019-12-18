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
nve0_graph_generate_unk46xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x404604, 0x14);
	nv_wr32(priv, 0x404608, 0x0);
	nv_wr32(priv, 0x40460c, 0x3fff);
	nv_wr32(priv, 0x404610, 0x100);
	nv_wr32(priv, 0x404618, 0x0);
	nv_wr32(priv, 0x40461c, 0x0);
	nv_wr32(priv, 0x404620, 0x0);
	nv_wr32(priv, 0x404624, 0x0);
	nv_wr32(priv, 0x40462c, 0x0);
	nv_wr32(priv, 0x404630, 0x0);
	nv_wr32(priv, 0x404640, 0x0);
	nv_wr32(priv, 0x404654, 0x0);
	nv_wr32(priv, 0x404660, 0x0);
	nv_wr32(priv, 0x404678, 0x0);
	nv_wr32(priv, 0x40467c, 0x2);
	nv_wr32(priv, 0x404680, 0x0);
	nv_wr32(priv, 0x404684, 0x0);
	nv_wr32(priv, 0x404688, 0x0);
	nv_wr32(priv, 0x40468c, 0x0);
	nv_wr32(priv, 0x404690, 0x0);
	nv_wr32(priv, 0x404694, 0x0);
	nv_wr32(priv, 0x404698, 0x0);
	nv_wr32(priv, 0x40469c, 0x0);
	nv_wr32(priv, 0x4046a0, 0x7f0080);
	nv_wr32(priv, 0x4046a4, 0x0);
	nv_wr32(priv, 0x4046a8, 0x0);
	nv_wr32(priv, 0x4046ac, 0x0);
	nv_wr32(priv, 0x4046b0, 0x0);
	nv_wr32(priv, 0x4046b4, 0x0);
	nv_wr32(priv, 0x4046b8, 0x0);
	nv_wr32(priv, 0x4046bc, 0x0);
	nv_wr32(priv, 0x4046c0, 0x0);
	nv_wr32(priv, 0x4046c8, 0x0);
	nv_wr32(priv, 0x4046cc, 0x0);
	nv_wr32(priv, 0x4046d0, 0x0);
}